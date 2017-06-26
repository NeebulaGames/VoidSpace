// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "WelderActor.generated.h"

UCLASS()
class VOIDSPACE_API AWelderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWelderActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere, Category = Audio)
	class USoundWave* WelderSound;

	UPROPERTY(VisibleAnywhere)
	class UEquipableComponent* EquipableComponent = nullptr;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* WelderMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* BeamStreamComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "WelderDebug")
	bool bUsingWelder = false;

	UPROPERTY(VisibleAnywhere, Category = "WelderDebug")
	class AOrtoHoleActor* Hole = nullptr;

	UFUNCTION()
	void Equipped();

	UFUNCTION()
	void Unequipped();

	UFUNCTION()
	void UseWelder();
	
	UFUNCTION()
	void EndUseWelder();
	
};
