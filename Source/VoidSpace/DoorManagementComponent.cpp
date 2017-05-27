// All rights Neebula Games

#include "VoidSpace.h"
#include "DoorManagementComponent.h"


// Sets default values for this component's properties
UDoorManagementComponent::UDoorManagementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UDoorManagementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bIsBeginExecution)
	{
		LockUnlockDoors();
	}
	else
	{
		GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UDoorManagementComponent::OnOverlap);
	}
}

void UDoorManagementComponent::LockUnlockDoors()
{
	for (AProximityDoor* door : Doors)
	{
		bOpenDoors ? door->OpenDoor() : door->CloseDoor();

		bBlockDoors ? door->Lock() : door->UnLock();
	}
}

void UDoorManagementComponent::OnOverlap(AActor* actor1, AActor* actor2)
{
	LockUnlockDoors();

	if (bOneShoot)
		DestroyComponent();
}
