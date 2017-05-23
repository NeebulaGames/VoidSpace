// All rights Neebula Games

#pragma once

#include "ExitVaultDoorAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class VOIDSPACE_API UExitVaultDoorAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BlindStates)
	bool bIsOpening;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BlindStates)
	bool bIsClosing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BlindStates)
	bool bIsOpened;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BlindStates)
	bool bIsClosed;
	
	
};
