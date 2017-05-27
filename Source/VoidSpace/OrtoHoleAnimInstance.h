// All rights Neebula Games

#pragma once

#include "Animation/AnimInstance.h"
#include "OrtoHoleAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSPACE_API UOrtoHoleAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HoleStates)
		bool bIsClosing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HoleStates)
		bool bIsOpened;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HoleStates)
		bool bIsClosed;
	
	
};
