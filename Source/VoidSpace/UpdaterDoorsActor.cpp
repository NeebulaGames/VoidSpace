// All rights Neebula Games

#include "VoidSpace.h"
#include "UpdaterDoorsActor.h"
#include "SpaceGameStateBase.h"
#include "DoorManagementComponent.h"


// Sets default values
AUpdaterDoorsActor::AUpdaterDoorsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DoorManagementComponent = CreateDefaultSubobject<UDoorManagementComponent>(TEXT("DoorManager"));
	RootComponent = DoorManagementComponent;
}

// Called when the game starts or when spawned
void AUpdaterDoorsActor::BeginPlay()
{
	Super::BeginPlay();
	
	manager = ASpaceGameStateBase::Instance(this)->GameEventManager;
	manager->OnEventStarted.AddDynamic(this, &AUpdaterDoorsActor::UpdateDoors);
}

void AUpdaterDoorsActor::UpdateDoors()
{
	if (!EventName.Equals(TEXT("")) && manager->GetCurrentEvent()->Name.Equals(EventName))
		DoorManagementComponent->LockUnlockDoors();
}

