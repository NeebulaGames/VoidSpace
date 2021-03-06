// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "OrtoHoleActor.generated.h"

UCLASS()
class PROJECTMILA_API AOrtoHoleActor : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHoleClosed);
	
public:	
	// Sets default values for this actor's properties
	AOrtoHoleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void Tick(float DeltaSeconds) override;

	void BeginClose();

	void StopClose();

	UPROPERTY(BlueprintAssignable, Category = HoleEvents)
	FOnHoleClosed OnHoleClosed;

	UPROPERTY(VisibleAnywhere, Category = HoleDebug)
	bool bRepaired = false;

private:

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* OxygenLeak;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* Sparks1;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* Sparks2;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* Sparks3;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* Sparks4;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* HoleMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = HoleDebug)
	bool bRepairing = false;

	UPROPERTY(VisibleAnywhere, Category = HoleDebug)
	UMaterialInstanceDynamic* HoleMaterial = nullptr;

	UPROPERTY(VisibleAnywhere, Category = HoleDebug)
	float Opacity = 1.f;
};
