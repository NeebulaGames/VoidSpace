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
	int LastDeathReason = -1;
	
	
};
