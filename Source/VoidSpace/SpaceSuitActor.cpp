// All rights Neebula Games

#include "VoidSpace.h"
#include "SpaceSuitActor.h"
#include "InteractableComponent.h"


// Sets default values
ASpaceSuitActor::ASpaceSuitActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = root;

	InteractableComponent = ObjectInitializer.CreateDefaultSubobject<UInteractableComponent>(this, TEXT("Interactable"));
	InteractableComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> spaceSuit(TEXT("StaticMesh'/Game/Meshes/SpaceSuit.SpaceSuit'"));
	SpaceSuitComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("SpaceSuit"));
	SpaceSuitComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	SpaceSuitComponent->SetStaticMesh(spaceSuit.Object);
}

// Called when the game starts or when spawned
void ASpaceSuitActor::BeginPlay()
{
	Super::BeginPlay();
}
