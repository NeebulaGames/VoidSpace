// All rights Neebula Games

#include "VoidSpace.h"
#include "UpdaterDoorsActor.h"


// Sets default values
AUpdaterDoorsActor::AUpdaterDoorsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	DoorManagementComponent = CreateDefaultSubobject<UDoorManagementComponent>(TEXT("DoorManager"));
}

// Called when the game starts or when spawned
void AUpdaterDoorsActor::BeginPlay()
{
	Super::BeginPlay();
	
	manager = ASpaceGameStateBase::Instance(this)->GameEventManager;
	manager->OnEventFinished.AddDynamic(this, &AUpdaterDoorsActor::UpdateDoors);
}

void AUpdaterDoorsActor::UpdateDoors()
{
	if (EndedEventName != "" && manager->GetCurrentEvent()->Name == EndedEventName)
		DoorManagementComponent->LockUnlockDoors();
}

