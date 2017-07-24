// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmergencyModuleActor.generated.h"

UCLASS()
class PROJECTMILA_API AEmergencyModuleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEmergencyModuleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 

	UFUNCTION()
	void OnEmergencyStart();

	UFUNCTION()
	void OnEmergencyFinish();

	UPROPERTY(VisibleAnywhere, Category = EmergencyModule, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category = EmergencyModule, meta = (AllowPrivateAccess = "true"))
	class ULedSwitchComponent* LedSwitchComponent;

	UPROPERTY(VisibleAnywhere, Category = EmergencyModule, meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* SpotlightComponent;

	float pitchRotation = 0.f;
	bool isLightOn = false;
};
