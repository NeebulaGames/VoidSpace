// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "LockerActor.generated.h"

UCLASS()
class PROJECTMILA_API ALockerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALockerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = Interactable, meta = (AllowPrivateAccess = "true"))
	class UInteractableComponent* InteractableComponent;

	UPROPERTY(VisibleAnywhere, Category = Interactable, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* LockerMeshComponent;

	UFUNCTION()
	void OnLockerUse();
	
};
