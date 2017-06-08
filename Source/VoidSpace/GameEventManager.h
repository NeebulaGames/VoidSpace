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
		bool bKillAtEnd = false;
		bool bSkipAfterDeath = false;
		float Time = 0.f;
		int DeathReason = 0;
		FEvent* NextEvent = nullptr;
		FString NextEventName = "";
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
	void StartEvents(bool skipAfterDeath);

	UFUNCTION(BlueprintCallable, Category = StateManagement)
	void FinishCurrentEvent();

	UFUNCTION(BlueprintCallable, Category = StateManagement)
	void SetTime(float time, bool runCountdown = true);

	UFUNCTION(BlueprintCallable, Category = StateManagement)
	float GetTime() const { return Time; }

	FEvent* GetCurrentEvent() const { return CurrentEvent; }

	UPROPERTY(BlueprintAssignable, Category = EventLifecycle)
	FOnEventFinished OnEventFinished;

	UPROPERTY(BlueprintAssignable, Category = EventLifecycle)
	FOnEventStarted OnEventStarted;

private:

	void LoadNextEvent();
	void SkipDeathEvents();

	float Time = 0;
	bool bIsFading = false;
	bool bCountDown = false;
	bool bStartMachine = false;

	FEvent* FirstEvent = nullptr;
	FEvent* CurrentEvent = nullptr;
};
