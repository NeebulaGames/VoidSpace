// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "SimonStandActor.generated.h"

UCLASS()
class VOIDSPACE_API ASimonStandActor : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimonCompleted);

public:
	// Sets default values for this actor's properties
	ASimonStandActor();

	UPROPERTY(BlueprintAssignable)
	FSimonCompleted OnSimonCompleted;

	UPROPERTY(VisibleAnywhere, Category = Interactable)
	class UInteractableComponent* InteractableComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void SimonCompleted();

	UFUNCTION()
	void EventStarted();

	UFUNCTION()
	void EventFinished();

	UPROPERTY(VisibleAnywhere, Category = SimonStand, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SimonStandMesh;

	bool bSimonCompleted = false;
};
