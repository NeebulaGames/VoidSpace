// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "PickableComponent.h"
#include "TributePickableComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTMILA_API UTributePickableComponent : public UPickableComponent
{
	GENERATED_BODY()
	
public:
	UTributePickableComponent();
	
	void PickedUp() override;

	class USoundWave* PachimariSound = nullptr;
};
