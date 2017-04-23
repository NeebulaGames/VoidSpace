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

	void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category=ElevatorInteractable)
	AActor* TeleportPosition;

	UPROPERTY(VisibleAnywhere, Category=ElevatorMesh)
	class USkeletalMeshComponent* ElevatorMesh;

	UPROPERTY(VisibleAnywhere, Category=ElevatorInteractable)
	class UInteractableComponent* InteractableComponent;

private:

	UFUNCTION()
	void OnElevatorEnter();

	UFUNCTION()
	void OnFadeOutFinish();

	bool bWasClosing = false;

	class UElevatorAnimInstance* AnimInstance;
};
