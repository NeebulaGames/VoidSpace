// All rights Neebula Games

#pragma once

#include "BlindAnimInstance.generated.h"

class ASimonStandActor;

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class VOIDSPACE_API UBlindAnimInstance : public UAnimInstance
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
	
	UFUNCTION()
	void OnSimonCompleted();

	UFUNCTION()
	void SetSimonStandToInstance(ASimonStandActor* SimonStand);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BlindStates)
	AMatineeActor* MeteorStorm;
};
