// All rights Neebula Games

#include "VoidSpace.h"
#include "SpaceSuitActor.h"
#include "InteractableComponent.h"


// Sets default values
ASpaceSuitActor::ASpaceSuitActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> spaceSuit(TEXT("StaticMesh'/Game/Meshes/SpaceSuit.SpaceSuit'"));
	SpaceSuitComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceSuit"));
	SpaceSuitComponent->SetupAttachment(RootComponent);
	SpaceSuitComponent->SetStaticMesh(spaceSuit.Object);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
	AddInstanceComponent(InteractableComponent);
}

// Called when the game starts or when spawned
void ASpaceSuitActor::BeginPlay()
{
	Super::BeginPlay();
}
