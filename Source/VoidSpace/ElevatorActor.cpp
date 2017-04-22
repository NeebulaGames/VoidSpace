// All rights Neebula Games

#include "VoidSpace.h"
#include "ElevatorActor.h"
#include "InteractableComponent.h"


// Sets default values
AElevatorActor::AElevatorActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	static ConstructorHelpers::FObjectFinder<UClass> elevatorBlueprint(TEXT("Class'/Game/Animations/Elevator/ElevatorAnim.ElevatorAnim_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> elevatorMesh(TEXT("SkeletalMesh'/Game/Meshes/Elevator/Elevator.Elevator'"));
	ElevatorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Elevator Mesh"));
	RootComponent = ElevatorMesh;
	ElevatorMesh->SetSkeletalMesh(elevatorMesh.Object);
	ElevatorMesh->SetAnimInstanceClass(elevatorBlueprint.Object);
	ElevatorMesh->SetCollisionProfileName(FName("BlockAll"));

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable Component"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->bRequireUseButton = false;
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(10.f, 10.f, 120.f));
}

// Called when the game starts or when spawned
void AElevatorActor::BeginPlay()
{
	Super::BeginPlay();
	
}
