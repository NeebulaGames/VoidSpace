// All rights Neebula Games

#include "VoidSpace.h"
#include "LockerActor.h"
#include "InteractableComponent.h"
#include "LockerAnimInstance.h"


// Sets default values
ALockerActor::ALockerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UClass> lockerBlueprint(TEXT("Class'/Game/Animations/Locker/LockerBlueprint.LockerBlueprint_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> locker(TEXT("SkeletalMesh'/Game/Meshes/Props/Locker/Locker.Locker'"));
	LockerMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Locker"));
	RootComponent = LockerMeshComponent;
	LockerMeshComponent->SetSkeletalMesh(locker.Object);
	LockerMeshComponent->SetAnimInstanceClass(lockerBlueprint.Object);
	LockerMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->bRequirePlayerNear = false;
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(30.f, 30.f, 90.f));
	InteractableComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	InteractableComponent->SetActive(true);
}

// Called when the game starts or when spawned
void ALockerActor::BeginPlay()
{
	Super::BeginPlay();
	InteractableComponent->OnTriggerAction.AddDynamic(this, &ALockerActor::OnLockerUse);
}

void ALockerActor::OnLockerUse()
{
	Cast<ULockerAnimInstance>(LockerMeshComponent->GetAnimInstance())->bIsOpening = true;

	InteractableComponent->DestroyComponent(true);
}
