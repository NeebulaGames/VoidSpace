// All rights Neebula Games

#include "VoidSpace.h"
#include "ExitVault.h"
#include "InteractableComponent.h"


// Sets default values
AExitVault::AExitVault()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> door(TEXT("SkeletalMesh'/Game/Meshes/Door/Door.Door'"));
	ExitInnerDoorMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DoorInner"));
	ExitInnerDoorMeshComponent->SetupAttachment(RootComponent);
	//ExitInnerDoorMeshComponent->SetSkeletalMesh(door.Object);
	//ExitInnerDoorMeshComponent->SetAnimInstanceClass(doorBlueprint.Object);
	ExitInnerDoorMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> door(TEXT("SkeletalMesh'/Game/Meshes/Door/Door.Door'"));
	ExitExternalDoorMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DoorExternal"));
	ExitExternalDoorMeshComponent->SetupAttachment(RootComponent);
	//ExitExternalDoorMeshComponent->SetSkeletalMesh(door.Object);
	//ExitExternalDoorMeshComponent->SetAnimInstanceClass(doorBlueprint.Object);
	ExitExternalDoorMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->bRequireUseButton = false;

	// Recalculate Box extension
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(130.f, 200.f, 120.f));

	//static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	//ParticleSystem->SetTemplate(PS.Object);
}


void AExitVault::OpenInnerDoor() const
{

}

void AExitVault::OpenExternalDoor() const
{

}

// Called when the game starts or when spawned
void AExitVault::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExitVault::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExitVault::OnVaultEnter()
{
	if (!isOutside)
	{
		// closing_door = inner_door
		// opening_door = external_door
	}
	else
	{
		// closing_door = external_door
		// opening_door = inner_door
	}

	// close closing_door

	// when doors are closed we can proceed 

	// particle effects

	// when particle effects finish we can proceed

	// open opening_door

	// Activate/Deactivate gravity
}

void AExitVault::OnVaultExit()
{
	isOutside = !isOutside;
}