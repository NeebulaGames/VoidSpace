// All rights Neebula Games

#pragma once

#include "GameEventManager.h"
#include "GameFramework/Actor.h"
#include "UnlockDoorsActor.generated.h"

UCLASS()
class VOIDSPACE_API AUnlockDoorsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnlockDoorsActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = Interactable, meta = (AllowPrivateAccess = "true"))
	class UDoorManagementComponent* DoorManagementComponent;

	UFUNCTION()
	void UpdateDoors();

	UGameEventManager* manager;
	
};
