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

	static ConstructorHelpers::FObjectFinder<UClass> doorBlueprint(TEXT("Class'/Game/Animations/Door/Doors_AnimatedBlueprint.Doors_AnimatedBlueprint_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> door(TEXT("SkeletalMesh'/Game/Meshes/Door/Doors_Animated.Doors_Animated'"));
	DoorMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Door"));
	DoorMeshComponent->SetupAttachment(RootComponent);
	DoorMeshComponent->SetSkeletalMesh(door.Object);
	DoorMeshComponent->SetAnimInstanceClass(doorBlueprint.Object);
	DoorMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->bRequireUseButton = false;
	InteractableComponent->bHighlight = false;
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(200.f, 200.f, 120.f));
}

// Called when the game starts or when spawned
void AProximityDoor::BeginPlay()
{
	Super::BeginPlay();

	InteractableComponent->OnTriggerEnter.AddDynamic(this, &AProximityDoor::OnDoorEnter);
	InteractableComponent->OnTriggerExit.AddDynamic(this, &AProximityDoor::OnDoorExit);

	DoorAnimInstance = Cast<UDoorAnimInstance>(DoorMeshComponent->GetAnimInstance());
}

void AProximityDoor::OnDoorEnter()
{
	if (!bLocked)
		DoorAnimInstance->bIsOpening = true;
}

void AProximityDoor::OnDoorExit()
{
	if (!bLocked)
		DoorAnimInstance->bIsClosing = true;
}

void AProximityDoor::Lock()
{
	bLocked = true;
}

void AProximityDoor::UnLock()
{
	bLocked = false;
}

void AProximityDoor::OpenDoor() const
{
	if (!DoorAnimInstance->bIsOpened)
		DoorAnimInstance->bIsOpening = true;
}

void AProximityDoor::CloseDoor() const
{
	if(!DoorAnimInstance->bIsClosed)
		DoorAnimInstance->bIsClosing = true;
}
