// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* EscapePodMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Interactable, meta = (AllowPrivateAccess = "true"))
	class UInteractableComponent* InteractableOpenComponent;

	UPROPERTY(VisibleAnywhere, Category = Interactable, meta = (AllowPrivateAccess = "true"))
	class UInteractableComponent* InteractableCloseComponent;

	UPROPERTY(VisibleAnywhere)
	class UEscapePodAnimInstance* EscapePodAnimInstance;

	UFUNCTION()
	void OnControlRoomEnter();
	
	UFUNCTION()
	void OnEscapePodEnter();

};
