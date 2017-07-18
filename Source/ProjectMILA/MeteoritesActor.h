// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeteoritesActor.generated.h"

UCLASS()
class PROJECTMILA_API AMeteoritesActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeteoritesActor();

	UFUNCTION()
	void StartEmission();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:	
	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ParticlesComponent = nullptr;
	
	UFUNCTION()
	void StopEmissionOnMeteor();
	
};
