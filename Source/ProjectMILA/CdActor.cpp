// All rights Neebula Games

#include "ProjectMILA.h"
#include "CdActor.h"
#include "PickableComponent.h"

// Sets default values
ACdActor::ACdActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> cd(TEXT("StaticMesh'/Game/Meshes/Cd.Cd'"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cd"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetStaticMesh(cd.Object);
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->bGenerateOverlapEvents = true;

	PickableComponent = CreateDefaultSubobject<UPickableComponent>(TEXT("Pickable"));
	PickableComponent->SetupAttachment(RootComponent);
}


