// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LightStateComponent.generated.h"


enum class ELightState : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMILA_API ULightStateComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	ULightStateComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	
private:

	void ChangeLighting(ELightState lightState);

	float LightIntensity;
	FLinearColor LightColor;
	ELightState CurrentState;
	ULightComponent* ParentLight;
	class ASpacestationManagementActor* StationManager;
};
