// All rights Neebula Games

#pragma once

#include "Engine/GameInstance.h"
#include "MoviePlayer.h"
#include "SpaceGameInstance.generated.h"

enum class EDeathReason : uint8;
/**
 * 
 */
UCLASS()
class PROJECTMILA_API USpaceGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* LoadedWorld);

	EDeathReason LastDeathReason = EDeathReason::None;
	
	FString CurrentMapName = "";
};
