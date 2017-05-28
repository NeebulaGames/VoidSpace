// All rights Neebula Games

#pragma once

#include "Animation/AnimInstance.h"
#include "LockerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSPACE_API ULockerAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LockerStates)
	bool bIsOpening;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LockerStates)
	bool bIsOpened;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LockerStates)
	bool bIsClosed;	
};
