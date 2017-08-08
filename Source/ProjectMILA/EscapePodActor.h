// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "InteractableComponent.h"
#include "EscapePodActor.generated.h"

UCLASS()
class PROJECTMILA_API AEscapePodActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEscapePodActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = ElevatorInteractable)
	AActor* TeleportPosition;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* EscapePodMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = InteractableOpen, meta = (AllowPrivateAccess = "true"))
	UInteractableComponent* InteractableOpenComponent;

	UPROPERTY(VisibleAnywhere, Category = InteractableClose, meta = (AllowPrivateAccess = "true"))
	UInteractableComponent* InteractableCloseComponent;

	UPROPERTY(VisibleAnywhere)
	class UEscapePodAnimInstance* EscapePodAnimInstance;

	UFUNCTION()
	void OnControlRoomEnter();
	
	UFUNCTION()
	void OnEscapePodEnter();

	UFUNCTION()
	void OnFadeOutFinish();

	bool bWasClosing = false;

};
