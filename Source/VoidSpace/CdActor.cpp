// All rights Neebula Games

#include "VoidSpace.h"
#include "CdActor.h"
#include "PickableComponent.h"


// Sets default values
ACdActor::ACdActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> cd(TEXT("StaticMesh'/Game/Meshes/Cd.Cd'"));
	StaticMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Cd"));
	StaticMeshComponent->SetStaticMesh(cd.Object);
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->bGenerateOverlapEvents = false;

	PickableComponent = ObjectInitializer.CreateDefaultSubobject<UPickableComponent>(this, TEXT("Pickable"));
	PickableComponent->SetupAttachment(StaticMeshComponent);
}


