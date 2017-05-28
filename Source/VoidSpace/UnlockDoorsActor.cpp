// All rights Neebula Games

#include "VoidSpace.h"
#include "UnlockDoorsActor.h"
#include "DoorManagementComponent.h"
#include "SpaceGameStateBase.h"


// Sets default values
AUnlockDoorsActor::AUnlockDoorsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	DoorManagementComponent = CreateDefaultSubobject<UDoorManagementComponent>(TEXT("DoorManager"));
}

// Called when the game starts or when spawned
void AUnlockDoorsActor::BeginPlay()
{
	Super::BeginPlay();

	manager = ASpaceGameStateBase::Instance(this)->GameEventManager;
	manager->OnEventFinished.AddDynamic(this, &AUnlockDoorsActor::UpdateDoors);
}

void AUnlockDoorsActor::UpdateDoors()
{
	if(manager->GetCurrentEvent()->Name == "Beginning")
		DoorManagementComponent->LockUnlockDoors();
}
