// All rights Neebula Games

#include "ProjectMILA.h"
#include "EscapePodActor.h"
#include "InteractableComponent.h"
#include "EscapePodAnimInstance.h"


// Sets default values
AEscapePodActor::AEscapePodActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> escapePod(TEXT("SkeletalMesh'/Game/Meshes/EscapePod/EscapePod.EscapePod'"));
	EscapePodMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Vitrine"));
	RootComponent = EscapePodMeshComponent;
	EscapePodMeshComponent->SetSkeletalMesh(escapePod.Object);
	EscapePodMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	static ConstructorHelpers::FObjectFinder<UClass> escapePodBlueprint(TEXT("Class'/Game/Animations/EscapePod/EscapePodBlueprint.EscapePodBlueprint_C'"));
	EscapePodMeshComponent->SetAnimInstanceClass(escapePodBlueprint.Object);

	InteractableOpenComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableToOpen"));
	InteractableOpenComponent->SetupAttachment(RootComponent);
	InteractableOpenComponent->bRequireUseButton = false;
	InteractableOpenComponent->bHighlight = false;
	InteractableOpenComponent->BoxComponent->SetBoxExtent(FVector(200.f, 200.f, 200.f));
	InteractableOpenComponent->BoxComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	InteractableCloseComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableToClose"));
	InteractableCloseComponent->SetupAttachment(RootComponent);
	InteractableCloseComponent->bRequireUseButton = false;
	InteractableCloseComponent->bHighlight = false;
	InteractableCloseComponent->BoxComponent->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	InteractableCloseComponent->BoxComponent->SetRelativeLocation(FVector(-50.f, -90.f, -60.f));

}

// Called when the game starts or when spawned
void AEscapePodActor::BeginPlay()
{
	Super::BeginPlay();

	InteractableOpenComponent->OnTriggerEnter.AddDynamic(this, &AEscapePodActor::OnControlRoomEnter);
	InteractableCloseComponent->OnTriggerEnter.AddDynamic(this, &AEscapePodActor::OnEscapePodEnter);
	
	EscapePodAnimInstance = Cast<UEscapePodAnimInstance>(EscapePodMeshComponent->GetAnimInstance());
}

void AEscapePodActor::OnControlRoomEnter()
{
	EscapePodAnimInstance->bIsOpening = true;
}

void AEscapePodActor::OnEscapePodEnter()
{
	EscapePodAnimInstance->bIsClosing = true;
}


