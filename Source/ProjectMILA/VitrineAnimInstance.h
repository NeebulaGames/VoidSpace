// All rights Neebula Games

#pragma once

#include "VitrineAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class PROJECTMILA_API UVitrineAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VitrineStates)
	bool bIsOpening;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VitrineStates)
	bool bIsClosing;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VitrineStates)
	bool bIsOpened;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VitrineStates)
	bool bIsClosed;
	
};
