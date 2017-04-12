// All rights Neebula Games

#pragma once

#include "GameEventManager.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSPACE_API UGameEventManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventFinished);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventStarted);

	struct FEvent 
	{
		bool bCountDown = false;
		float Time = 0.f;
		int DeathReason = 0;
		FEvent* NextEvent = nullptr;
		FString Name;
		FString LevelName = "";
	};

public:

	void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableWhenPaused() const override;
	bool IsTickableInEditor() const override;
	TStatId GetStatId() const override;
	UWorld* GetWorld() const override;

	void LoadEventsFromFile(FString& fileName);
	void StartEvents();
	void FinishCurrentEvent();
	void SetTime(float time, bool runCountdown = true);

	FEvent* GetCurrentEvent() const { return CurrentEvent; }

	UPROPERTY(BlueprintAssignable, Category = EventLifecycle)
	FOnEventFinished OnEventFinished;

	UPROPERTY(BlueprintAssignable, Category = EventLifecycle)
	FOnEventStarted OnEventStarted;
	
private:

	void LoadNextEvent();

	float Time = 0;
	bool bCountDown = false;

	FEvent* FirstEvent = nullptr;
	FEvent* CurrentEvent = nullptr;
};
