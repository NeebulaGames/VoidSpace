// All rights Neebula Games

#include "VoidSpace.h"
#include "SpaceGameStateBase.h"
#include "SpaceCharacter.h"
#include "GameEventManager.h"

ASpaceGameStateBase::ASpaceGameStateBase()
{
	GameEventManager = CreateDefaultSubobject<UGameEventManager>("GameEventManager");
}

void ASpaceGameStateBase::BeginPlay()
{
	FString eventsFile(TEXT("events.json"));
	GameEventManager->LoadEventsFromFile(eventsFile);
	GameEventManager->StartEvents();
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

void ASpaceGameStateBase::FinishEvent()
{
	GameEventManager->FinishCurrentEvent();
}

ASpaceGameStateBase* ASpaceGameStateBase::Instance(UObject* world)
{
	return Cast<ASpaceGameStateBase>(UGameplayStatics::GetGameState(world));
}
