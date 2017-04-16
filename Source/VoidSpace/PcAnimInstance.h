// All rights Neebula Games

#pragma once

#include "PcAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class VOIDSPACE_API UPcAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CdStates)
		bool bIsInserting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CdStates)
		bool bIsInserted;
	
};
