// All rights Neebula Games

#include "ProjectMILA.h"
#include "InteractableComponent.h"
#include "ExitVaultLever.h"
#include "LeverAnimInstance.h"


// Sets default values
AExitVaultLever::AExitVaultLever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UClass> leverBlueprint(TEXT("AnimBlueprint'/Game/Animations/Lever/LeverBlueprint.LeverBlueprint_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> lever(TEXT("SkeletalMesh'/Game/Meshes/Props/Lever/ExitVaultLever.ExitVaultLever'"));
	LeverMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Lever"));
	RootComponent = LeverMeshComponent;
	LeverMeshComponent->SetSkeletalMesh(lever.Object);
	LeverMeshComponent->SetAnimInstanceClass(leverBlueprint.Object);
	LeverMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->bRequirePlayerNear = false;
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(30.f, 30.f, 90.f));
	InteractableComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	InteractableComponent->SetActive(true);

}

// Called when the game starts or when spawned
void AExitVaultLever::BeginPlay()
{
	Super::BeginPlay();
}

bool AExitVaultLever::IsTriggering()
{
	return Cast<ULeverAnimInstance>(LeverMeshComponent->GetAnimInstance())->bIsTriggering;
}

bool AExitVaultLever::IsNotTriggered()
{
	return Cast<ULeverAnimInstance>(LeverMeshComponent->GetAnimInstance())->bIsNotTriggered;
}

void AExitVaultLever::SetbIsTriggering(bool value)
{
	Cast<ULeverAnimInstance>(LeverMeshComponent->GetAnimInstance())->bIsTriggering = value;
}

void AExitVaultLever::SetbIsNotTriggered(bool value)
{
	Cast<ULeverAnimInstance>(LeverMeshComponent->GetAnimInstance())->bIsNotTriggered = value;
}

