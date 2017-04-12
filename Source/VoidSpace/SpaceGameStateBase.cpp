// All rights Neebula Games

#include "VoidSpace.h"
#include "SpaceGameStateBase.h"
#include "SpaceCharacter.h"
#include "GameEventManager.h"
#include "SpaceGameInstance.h"

ASpaceGameStateBase::ASpaceGameStateBase()
{
	GameEventManager = CreateDefaultSubobject<UGameEventManager>("GameEventManager");
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
		character->ToggleSpaceSuit(activate);
	}
}

void ASpaceGameStateBase::Die(int reason)
{
	ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (character)
	{
		character->KillPlayer(reason);
	}

	static_cast<USpaceGameInstance*>(GetGameInstance())->LastDeathReason = reason;

	// TODO: Wait for player animation trigger if necessary
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void ASpaceGameStateBase::FinishEvent()
{
	GameEventManager->FinishCurrentEvent();
}

ASpaceGameStateBase* ASpaceGameStateBase::Instance(UObject* world)
{
	return Cast<ASpaceGameStateBase>(UGameplayStatics::GetGameState(world));
}
