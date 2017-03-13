// All rights Neebula Games

#include "VoidSpace.h"
#include "ProximityDoor.h"


// Sets default values
AProximityDoor::AProximityDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProximityDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProximityDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

