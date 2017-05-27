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
	bool IsBeginExecution;

	UPROPERTY(EditAnywhere, Category = Execution)
	bool OpenDoors;

	UPROPERTY(EditAnywhere, Category = Execution)
	bool BlockDoors;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	void lockUnlockDoors();

	UPROPERTY(EditAnywhere, Category = DoorList, meta = (AllowPrivateAccess = "true"))
	TArray<AProximityDoor*> doors;

	UFUNCTION()
	void OnOverlap(AActor* actor1, AActor* actor2);
		
	
};
