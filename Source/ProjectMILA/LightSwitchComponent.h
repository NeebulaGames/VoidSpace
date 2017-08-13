// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceStatics.h"
#include "LightSwitchComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMILA_API ULightSwitchComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULightSwitchComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void SetLightState(ELightState state);

	ELightState CurrentState;
	class ASpacestationManagementActor* StationManager;
	UMaterialInstanceDynamic* MaterialInstance;
	
};
