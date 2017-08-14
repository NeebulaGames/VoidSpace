// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EscapePodAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class PROJECTMILA_API UEscapePodAnimInstance : public UAnimInstance
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
