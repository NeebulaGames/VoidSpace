// All rights Neebula Games

#pragma once

#include "Animation/AnimInstance.h"
#include "ElevatorAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class VOIDSPACE_API UElevatorAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ElevatorStates)
	bool bIsOpening;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ElevatorStates)
	bool bIsClosing;

};
