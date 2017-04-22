// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "ElevatorActor.generated.h"

UCLASS()
class VOIDSPACE_API AElevatorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevatorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	class USkeletalMeshComponent* ElevatorMesh;

	class UInteractableComponent* InteractableComponent;
	
};
