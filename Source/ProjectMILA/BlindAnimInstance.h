// All rights Neebula Games

#pragma once
#include "BlindAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class PROJECTMILA_API UBlindAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = BlindStates)
	bool bIsOpening;

	UPROPERTY(EditAnywhere, Category = BlindStates)
	bool bIsClosing;

	UPROPERTY(EditAnywhere, Category = BlindStates)
	bool bIsOpened;

	UPROPERTY(EditAnywhere, Category = BlindStates)
	bool bIsClosed;

	UFUNCTION(BlueprintCallable, Category = EventSystem)
	bool IsBeginningEvent();
};
