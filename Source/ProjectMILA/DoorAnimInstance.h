// All rights Neebula Games

#pragma once

#include "DoorAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class PROJECTMILA_API UDoorAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DoorStates)
	bool bIsOpening;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DoorStates)
	bool bIsClosing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DoorStates)
	bool bIsOpened;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DoorStates)
	bool bIsClosed;
};
