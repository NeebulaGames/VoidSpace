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

	UPROPERTY(VisibleAnywhere)
	class UEquipableComponent* EquipableComponent = nullptr;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* WelderMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* BeamStreamComponent = nullptr;

	UFUNCTION()
	void Equipped();

	UFUNCTION()
	void Unequipped();

	UFUNCTION()
	void UseWelder();
	
	UFUNCTION()
	void EndUseWelder();
	
};
