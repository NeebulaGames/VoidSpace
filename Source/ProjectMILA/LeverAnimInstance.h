// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LeverAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMILA_API ULeverAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LockerStates)
	bool bIsTriggering;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LockerStates)
	bool bIsNotTriggered;

};
