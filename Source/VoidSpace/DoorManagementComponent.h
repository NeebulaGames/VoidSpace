// All rights Neebula Games

#pragma once

#include "Components/ActorComponent.h"
#include "ProximityDoor.h"
#include "DoorManagementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOIDSPACE_API UDoorManagementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorManagementComponent();

	UPROPERTY(EditAnywhere, Category = Execution)
	bool bOneShoot;

	UPROPERTY(EditAnywhere, Category = Execution)
	bool bIsBeginExecution;

	UPROPERTY(EditAnywhere, Category = Execution)
	bool bOpenDoors;

	UPROPERTY(EditAnywhere, Category = Execution)
	bool bBlockDoors;

	void LockUnlockDoors();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = DoorList, meta = (AllowPrivateAccess = "true"))
	TArray<AProximityDoor*> Doors;

	UFUNCTION()
	void OnOverlap(AActor* actor1, AActor* actor2);
		
	
};
