// All rights Neebula Games

#include "VoidSpace.h"
#include "GameEventManager.h"
#include "SpaceGameStateBase.h"
#include "SpaceGameInstance.h"


void UGameEventManager::Tick(float DeltaTime)
{
	if (bCountDown && Time < 0.f)
	{
		ASpaceGameStateBase::Instance(GetWorld())->Die(CurrentEvent->DeathReason);
	}
	else
	{
		Time -= DeltaTime;
	}
}

bool UGameEventManager::IsTickable() const
{
	return true;
}

bool UGameEventManager::IsTickableWhenPaused() const
{
	return false;
}

bool UGameEventManager::IsTickableInEditor() const
{
	return false;
}

TStatId UGameEventManager::GetStatId() const
{
	return TStatId();
}

UWorld* UGameEventManager::GetWorld() const
{
	return GetOuter()->GetWorld();
}

void UGameEventManager::LoadEventsFromFile(FString& fileName)
{
	UE_LOG(EventSM, Log, TEXT("Loading events from file %s"), *fileName);
	// TODO: Implement JSON load
	FirstEvent = new FEvent;
	FirstEvent->Name = "Beginning";
	FirstEvent->LevelName = "Beginning";
	FirstEvent->Time = 10;
	FirstEvent->bCountDown = true;
	FirstEvent->DeathReason = 2;
	FirstEvent->bSkipAfterDeath = true;
	FEvent* next = new FEvent;
	next->Name = "End";
	next->LevelName = "End";
	FirstEvent->NextEvent = next;
	UE_LOG(EventSM, Log, TEXT("Loaded %d events"), 2);
}

void UGameEventManager::StartEvents(bool skipDeath)
{
	UE_LOG(EventSM, Log, TEXT("Starting event SM"));
	if (skipDeath)
		SkipDeathEvents();
	if (FirstEvent)
	{
		CurrentEvent = FirstEvent;
		LoadNextEvent();
	}
}

void UGameEventManager::FinishCurrentEvent()
{
	OnEventFinished.Broadcast();

	FLatentActionInfo info;
	UGameplayStatics::UnloadStreamLevel(GetWorld(), FName(*CurrentEvent->LevelName), info);

	UE_LOG(EventSM, Log, TEXT("Finish event %s"), *CurrentEvent->Name);

	if (CurrentEvent->NextEvent)
	{
		FEvent* to_delete = CurrentEvent;
		CurrentEvent = CurrentEvent->NextEvent;
		delete to_delete;
		LoadNextEvent();
	}
	else
	{
		UE_LOG(EventSM, Log, TEXT("Reached last event"));
		ASpaceGameStateBase::Instance(GetWorld())->EndGame();
	}
}

void UGameEventManager::SetTime(float time, bool run)
{
	Time = time;
	bCountDown = run;
}

void UGameEventManager::LoadNextEvent()
{
	UE_LOG(EventSM, Log, TEXT("Loading event %s"), *CurrentEvent->Name);
	FLatentActionInfo info;
	UGameplayStatics::LoadStreamLevel(GetWorld(), FName(*CurrentEvent->LevelName), true, true, info);
	Time = CurrentEvent->Time;
	bCountDown = CurrentEvent->bCountDown;
	OnEventStarted.Broadcast();
}

void UGameEventManager::SkipDeathEvents()
{
	while (FirstEvent && FirstEvent->bSkipAfterDeath)
		FirstEvent = FirstEvent->NextEvent;
}
