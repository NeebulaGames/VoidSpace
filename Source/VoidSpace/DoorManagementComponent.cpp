// All rights Neebula Games

#include "VoidSpace.h"
#include "DoorManagementComponent.h"
#include "SpaceGameStateBase.h" 

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
	
	manager = ASpaceGameStateBase::Instance(this)->GameEventManager;

	if (StartTrigger == EDoorStartTriggerEnum::DSTE_OnBeginExecution) 
	{ 
		LockUnlockDoors(); 
	}
	else if (StartTrigger == EDoorStartTriggerEnum::DSTE_OnBeginEvent)
	{ 
		manager->OnEventStarted.AddDynamic(this, &UDoorManagementComponent::UpdateDoors);
	} 
	else if (StartTrigger == EDoorStartTriggerEnum::DSTE_OnOverlap)
	{ 
		manager->OnEventStarted.AddDynamic(this, &UDoorManagementComponent::UpdateOverlap);
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

void UDoorManagementComponent::UpdateDoors()
{
	if (!EventName.Equals(TEXT("")) && manager->GetCurrentEvent()->Name.Equals(EventName))
		LockUnlockDoors();
}

void UDoorManagementComponent::UpdateOverlap()
{
	if (!EventName.Equals(TEXT("")) && manager->GetCurrentEvent()->Name.Equals(EventName))
		GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UDoorManagementComponent::OnOverlap);
	else
		GetOwner()->OnActorBeginOverlap.RemoveDynamic(this, &UDoorManagementComponent::OnOverlap);
}