// All rights Neebula Games

#pragma once

#include "Engine/GameInstance.h"
#include "SpaceGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSPACE_API USpaceGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
	virtual void EndLoadingScreen();

	int LastDeathReason = -1;
	
	
};
