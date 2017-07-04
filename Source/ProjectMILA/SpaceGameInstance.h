// All rights Neebula Games

#pragma once

#include "Engine/GameInstance.h"
#include "SpaceGameInstance.generated.h"

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

	int LastDeathReason = -1;
	
	
};
