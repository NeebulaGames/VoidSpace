// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceStatics.h"
#include "LedSwitchComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOIDSPACE_API ULedSwitchComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULedSwitchComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	ELedState CurrentState;
	class ASpacestationManagementActor* StationManager;
	UMaterialInstanceDynamic* MaterialInstance;
	
};
