// All rights Neebula Games

#include "VoidSpace.h"
#include "ProximityDoor.h"
#include "InteractableComponent.h"
#include "DoorAnimInstance.h"


// Sets default values
AProximityDoor::AProximityDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	static ConstructorHelpers::FObjectFinder<UClass> doorBlueprint(TEXT("Class'/Game/Animations/DoorBlueprint.DoorBlueprint_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> door(TEXT("SkeletalMesh'/Game/Meshes/Door/Door.Door'"));
	DoorMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Door"));
	DoorMeshComponent->SetupAttachment(RootComponent);
	DoorMeshComponent->SetSkeletalMesh(door.Object);
	DoorMeshComponent->SetAnimInstanceClass(doorBlueprint.Object);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->bRequireUseButton = false;
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(130.f, 200.f, 120.f));
}

// Called when the game starts or when spawned
void AProximityDoor::BeginPlay()
{
	Super::BeginPlay();

	InteractableComponent->OnTriggerEnter.AddDynamic(this, &AProximityDoor::OnDoorEnter);
	InteractableComponent->OnTriggerExit.AddDynamic(this, &AProximityDoor::OnDoorExit);
}

void AProximityDoor::OnDoorEnter()
{
	if (!locked)
		OpenDoor();
}

void AProximityDoor::OnDoorExit()
{
	if (!locked)
		CloseDoor();
}

void AProximityDoor::Lock()
{
	UE_LOG(LogTemp, Warning, TEXT("Door locked"));
	locked = true;
}

void AProximityDoor::UnLock()
{
	UE_LOG(LogTemp, Warning, TEXT("Door unlocked"));
	locked = false;
}

void AProximityDoor::OpenDoor() const
{
	Cast<UDoorAnimInstance>(DoorMeshComponent->GetAnimInstance())->bIsOpening = true;
}

void AProximityDoor::CloseDoor() const
{
	Cast<UDoorAnimInstance>(DoorMeshComponent->GetAnimInstance())->bIsClosing = true;
}
