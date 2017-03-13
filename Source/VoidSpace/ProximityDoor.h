// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "ProximityDoor.generated.h"

UCLASS()
class VOIDSPACE_API AProximityDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProximityDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = DoorMesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* DoorMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Interactable, meta = (AllowPrivateAccess = "true"))
	class UInteractableComponent* InteractableComponent;
	
	UFUNCTION()
	void OnDoorEnter();

	UFUNCTION()
	void OnDoorExit();
};
