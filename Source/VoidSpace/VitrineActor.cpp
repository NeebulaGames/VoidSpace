// All rights Neebula Games

#include "VoidSpace.h"
#include "VitrineActor.h"
#include "InteractableComponent.h"
#include "IdCardActor.h"
#include "VitrineAnimInstance.h"
#include "SpaceCharacter.h"


// Sets default values
AVitrineActor::AVitrineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	static ConstructorHelpers::FObjectFinder<UClass> vitrineBlueprint(TEXT("Class'/Game/Animations/Vitrine/VitrineBlueprint.VitrineBlueprint_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> vitrine(TEXT("SkeletalMesh'/Game/Meshes/Vitrine/Vitrine.Vitrine'"));
	VitrineMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Vitrine"));
	VitrineMeshComponent->SetupAttachment(RootComponent);
	VitrineMeshComponent->SetSkeletalMesh(vitrine.Object);
	VitrineMeshComponent->SetAnimInstanceClass(vitrineBlueprint.Object);
	VitrineMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("VitrineInteractable"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->SetRelativeLocation(FVector(-70.f, 20.f, 95.f));
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(13.5f, 16.5f, 10.f));
	InteractableComponent->BoxComponent->SetRelativeRotation(FRotator(0.f, 151.f, 0.f));
	InteractableComponent->BoxComponent->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void AVitrineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVitrineActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(AIdCardActor::StaticClass()))
	{
		ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		Cast<UVitrineAnimInstance>(VitrineMeshComponent->GetAnimInstance())->bIsOpening = true;
		character->pickedObject->Destroy();
		character->ReleaseObject();
	}
}

