// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceStatics.h"
#include "BlinkLights.generated.h"


UENUM(BlueprintType)
enum class EBlinkLightState : uint8
{
	BLINK_OFF,
	BLINK_TURNING_ON
};

UCLASS()
class PROJECTMILA_API ABlinkLights : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlinkLights();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	EBlinkLightState CurrentBlinkState;

	float CurrentColor = 1.f;

	void BlinkLights();
	void ChangeLighting(ELightState lightState);

	ELightState CurrentState;

	float Counter = 0.f;
	float DelayON = 0.f;
	float DelayOFF = 0.f;

	class ASpacestationManagementActor* StationManager;

	UMaterialInstanceDynamic* MaterialInstanceLeft;
	UMaterialInstanceDynamic* MaterialInstanceRight;

	float LightIntensity;
	FLinearColor LightColor;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UPointLightComponent* CorridorCentralLight;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CorridorLeftLight;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CorridorRightLight;
};
