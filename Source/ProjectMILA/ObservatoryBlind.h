// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "SimonStandActor.h"
#include "ObservatoryBlind.generated.h"

UCLASS()
class PROJECTMILA_API AObservatoryBlind : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObservatoryBlind();

	UPROPERTY(EditAnywhere, Category = SimonStand)
	class ASimonStandActor* SimonStand;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, Category = BlindMesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* BlindMeshComponent;	
	
	UFUNCTION()
	void OnSimonCompleted();
};
