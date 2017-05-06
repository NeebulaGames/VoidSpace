// All rights Neebula Games

#include "VoidSpace.h"
#include "CdActor.h"
#include "PickableComponent.h"
#include "InteractableComponent.h"


// Sets default values
ACdActor::ACdActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> cd(TEXT("StaticMesh'/Game/Meshes/Cd.Cd'"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cd"));
	StaticMeshComponent->SetStaticMesh(cd.Object);
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->bGenerateOverlapEvents = false;

	PickableComponent = CreateDefaultSubobject<UPickableComponent>(TEXT("Pickable"));

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(StaticMeshComponent);
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(11.f, 11.f, 0.5f));
}


