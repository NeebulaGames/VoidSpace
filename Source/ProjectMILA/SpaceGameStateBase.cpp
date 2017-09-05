// All rights Neebula Games

#include "ProjectMILA.h"
#include "SpaceGameStateBase.h"
#include "SpaceCharacter.h"
#include "GameEventManager.h"
#include "SpaceGameInstance.h"
#include "SpacestationManagementActor.h"
#include "SpaceSuitActor.h"

static TAutoConsoleVariable<int32> CVarSkipCinematics(
	TEXT("d.SkipCinematics"),
	0,
	TEXT("Specifies if cinematics should be skipped\n"),
	ECVF_Cheat);

ASpaceGameStateBase::ASpaceGameStateBase()
{
	GameEventManager = CreateDefaultSubobject<UGameEventManager>("GameEventManager");
	DialogueManager = CreateDefaultSubobject<UDialogueManager>("DialogueManager");
}

void ASpaceGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	TActorIterator<ASpacestationManagementActor> managerItr(GetWorld());
	
	if (managerItr)
		SpacestationManager = *managerItr;

	USpaceGameInstance* gameInstance = static_cast<USpaceGameInstance*>(GetGameInstance());

	if (gameInstance->LastDeathReason == EDeathReason::None)
	{
		gameInstance->BeginPlayTime = FDateTime::Now();
	}
}

void ASpaceGameStateBase::StartEventSM()
{
	FString eventsFile(TEXT("events.json"));
	GameEventManager->LoadEventsFromFile(eventsFile);

	EDeathReason lastDeathReason = static_cast<USpaceGameInstance*>(GetGameInstance())->LastDeathReason;

	if (bLoadEventSM)
		GameEventManager->StartEvents(lastDeathReason != EDeathReason::None);

	UE_LOG(LogGameState, Log, TEXT("Last death reason %d"), static_cast<uint8>(lastDeathReason));
}

void ASpaceGameStateBase::TogglePlayerGravity() const
{
	ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (character)
	{
		character->ToggleGravity();
	}
}

void ASpaceGameStateBase::ToggleSpaceSuit(bool activate) const
{
	ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (character)
	{
		ASpaceSuitActor* spaceSuit = nullptr;
		if (activate)
			spaceSuit = *TActorIterator<ASpaceSuitActor>(GetWorld());
		character->ToggleSpaceSuit(spaceSuit);
	}
}

bool ASpaceGameStateBase::Die(EDeathReason reason)
{
	ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (character)
	{
		if (reason == EDeathReason::Choke && character->WearsSpaceSuit() && !character->GetEquippedSuit()->IsConsumingOxygen())
		{
			character->ToggleOxygen(true);
			return false;
		}
		else
		{
			USpaceGameInstance* gameInstance = static_cast<USpaceGameInstance*>(GetGameInstance());
			gameInstance->LastDeathReason = reason;
			++gameInstance->Retries;

			if (reason == EDeathReason::Choke && !character->IsGravityEnabled())
				reason = EDeathReason::ChokeSpacesuit;

			float length = character->KillPlayer(reason);

			if (length > 0)
			{
				FTimerHandle unused;
				FTimerDelegate callback;
				callback.BindLambda([this]() -> void {UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false); });
				GetWorldTimerManager().SetTimer(unused, callback, length, false);
			}
			else
			{
				UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
			}
		}
	}

	return true;
}

void ASpaceGameStateBase::EndGame()
{
	static_cast<USpaceGameInstance*>(GetGameInstance())->ResetStats();

	// TODO: Transition to credits?
	UGameplayStatics::OpenLevel(this, TEXT("MainMenu"), false);
}

void ASpaceGameStateBase::FinishEvent()
{
	GameEventManager->FinishCurrentEvent();
}

void ASpaceGameStateBase::EnablePlayerInput() const
{
	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	character->EnableInput(controller);
}

void ASpaceGameStateBase::DisablePlayerInput() const
{
	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	character->DisableInput(controller);
}

bool ASpaceGameStateBase::IsInputEnabled() const
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	return controller->InputEnabled();
}

bool ASpaceGameStateBase::SkipCinematics()
{
	return CVarSkipCinematics.GetValueOnGameThread() != 0;
}

ASpaceGameStateBase* ASpaceGameStateBase::Instance(UObject* world)
{
	return Cast<ASpaceGameStateBase>(UGameplayStatics::GetGameState(world));
}
