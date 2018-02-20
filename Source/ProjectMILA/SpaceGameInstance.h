// All rights Neebula Games

#pragma once

#include "Engine/GameInstance.h"
#include "MoviePlayer.h"
#include "SpaceStatics.h"
#include "SpaceGameInstance.generated.h"

enum class EDeathReason : uint8;
/**
 * 
 */
UCLASS(config=Game)
class PROJECTMILA_API USpaceGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* LoadedWorld);

	void ResetStats();

	UFUNCTION(Exec)
	void SwapYAxis();

	UFUNCTION(BlueprintCallable)
	void SaveConfig();

	UFUNCTION(BlueprintCallable)
	void LoadConfig();

	EDeathReason LastDeathReason = EDeathReason::None;
	
	FString CurrentMapName = "";

	FDateTime BeginPlayTime;

	int Retries = 0;

	UPROPERTY(Config, BlueprintReadWrite)
	bool InvertYAxis = false;
};
