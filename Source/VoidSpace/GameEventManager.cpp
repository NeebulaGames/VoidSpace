// All rights Neebula Games

#include "VoidSpace.h"
#include "GameEventManager.h"
#include "SpaceGameStateBase.h"
#include "SpaceGameInstance.h"
#include <map>


void UGameEventManager::Tick(float DeltaTime)
{
	if (bCountDown && Time <= 0.f)
	{
		ASpaceGameStateBase::Instance(GetWorld())->Die(CurrentEvent->DeathReason);
	}
	else if (bCountDown)
	{
		Time -= DeltaTime;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString("Time remaining ").Append(FString::FromInt(Time)).Append("s"));
	}

	if (bStartMachine) 
	{
		LoadNextEvent();
		bStartMachine = false;
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

	const FString path = FPaths::Combine(FPaths::Combine(*FPaths::GameContentDir(), *FString("Data")), *fileName);
	FString jsonContent;

	FFileHelper::LoadFileToString(jsonContent, *path);
	TSharedPtr<FJsonObject> jsonObject;
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(jsonContent);

	if (FJsonSerializer::Deserialize(reader, jsonObject))
	{
		std::map<FString, FEvent*> eventMap;

		TArray<TSharedPtr<FJsonValue>> eventList = jsonObject->GetArrayField(TEXT("EventList"));

		for (TSharedPtr<FJsonValue> val : eventList)
		{
			TSharedPtr<FJsonObject> obj = val->AsObject();
			FEvent* ev = new FEvent;
			ev->Name = obj->GetStringField("Name");
			ev->LevelName = obj->GetStringField("LevelName");
			ev->bCountDown = obj->GetBoolField("CountDown");
			ev->bSkipAfterDeath = obj->GetBoolField("SkipAfterDeath");
			ev->Time = obj->GetNumberField("Time");
			ev->DeathReason = obj->GetIntegerField("DeathReason");
			ev->NextEventName = obj->GetStringField("NextEvent");

			eventMap[ev->Name] = ev;
		}

		for (auto ev : eventMap)
		{
			FString nextEvent = ev.second->NextEventName;
			if (!nextEvent.IsEmpty())
				ev.second->NextEvent = eventMap[nextEvent];
		}

		FirstEvent = eventMap[jsonObject->GetStringField("FirstEvent")];
	}
}

void UGameEventManager::StartEvents(bool skipDeath)
{
	UE_LOG(EventSM, Log, TEXT("Starting event SM"));
	if (skipDeath)
		SkipDeathEvents();
	if (FirstEvent)
	{
		CurrentEvent = FirstEvent;
		bStartMachine = true;
	}
}

void UGameEventManager::FinishCurrentEvent()
{
	OnEventFinished.Broadcast();

	FLatentActionInfo info;
	info.UUID = 1;
	UGameplayStatics::UnloadStreamLevel(this, FName(*CurrentEvent->LevelName), info);

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
	info.UUID = 0;
	UGameplayStatics::LoadStreamLevel(this, FName(*CurrentEvent->LevelName), true, true, info);
	Time = CurrentEvent->Time;
	bCountDown = CurrentEvent->bCountDown;
	OnEventStarted.Broadcast();
}

void UGameEventManager::SkipDeathEvents()
{
	while (FirstEvent && FirstEvent->bSkipAfterDeath)
		FirstEvent = FirstEvent->NextEvent;
}
