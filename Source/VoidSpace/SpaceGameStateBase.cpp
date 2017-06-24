// All rights Neebula Games

#include "VoidSpace.h"
#include "SpaceGameStateBase.h"
#include "SpaceCharacter.h"
#include "GameEventManager.h"
#include "SpaceGameInstance.h"
#include "SpacestationManagementActor.h"
#include "SpaceSuitActor.h"

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
}

void ASpaceGameStateBase::StartEventSM()
{
	FString eventsFile(TEXT("events.json"));
	GameEventManager->LoadEventsFromFile(eventsFile);

	int lastDeathReason = static_cast<USpaceGameInstance*>(GetGameInstance())->LastDeathReason;

	if (bLoadEventSM)
		GameEventManager->StartEvents(lastDeathReason != -1);

	UE_LOG(LogGameState, Log, TEXT("Last death reason %d"), lastDeathReason);
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

void ASpaceGameStateBase::Die(int reason)
{
	ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (character)
	{
		if (reason == 2 && character->WearsSpaceSuit() && !character->GetEquippedSuit()->IsConsumingOxygen())
			character->GetEquippedSuit()->StartConsumingOxygen();
		else
		{
			character->KillPlayer(reason);

			static_cast<USpaceGameInstance*>(GetGameInstance())->LastDeathReason = reason;

			// TODO: Wait for player animation trigger if necessary
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		}
	}
}

void ASpaceGameStateBase::EndGame()
{
	// TODO: Transition to credits?
	static_cast<USpaceGameInstance*>(GetGameInstance())->LastDeathReason = -1;
	UGameplayStatics::OpenLevel(this, TEXT("MainMenu"), false);
}

void ASpaceGameStateBase::FinishEvent()
{
	GameEventManager->FinishCurrentEvent();
}

ASpaceGameStateBase* ASpaceGameStateBase::Instance(UObject* world)
{
	return Cast<ASpaceGameStateBase>(UGameplayStatics::GetGameState(world));
}
