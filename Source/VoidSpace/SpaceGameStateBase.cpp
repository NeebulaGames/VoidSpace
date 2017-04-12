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

void ASpaceGameStateBase::BeginPlay()
{
	FString eventsFile(TEXT("events.json"));
	GameEventManager->LoadEventsFromFile(eventsFile);
	GameEventManager->StartEvents();

	UE_LOG(LogGameState, Log, TEXT("Last death reason %d"), static_cast<USpaceGameInstance*>(GetGameInstance())->LastDeathReason);
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
