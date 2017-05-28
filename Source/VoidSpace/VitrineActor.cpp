// All rights Neebula Games

#include "VoidSpace.h"
#include "VitrineActor.h"
#include "InteractableComponent.h"
#include "IdCardActor.h"
#include "VitrineAnimInstance.h"
#include "SpaceCharacter.h"
#include "SpaceSuitActor.h"


// Sets default values
AVitrineActor::AVitrineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> vitrine(TEXT("SkeletalMesh'/Game/Meshes/Vitrine/Vitrine.Vitrine'"));
	VitrineMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Vitrine"));
	RootComponent = VitrineMeshComponent;
	VitrineMeshComponent->SetSkeletalMesh(vitrine.Object); 
	VitrineMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	static ConstructorHelpers::FObjectFinder<UClass> vitrineBlueprint(TEXT("Class'/Game/Animations/Vitrine/VitrineBlueprint.VitrineBlueprint_C'"));
	VitrineMeshComponent->SetAnimInstanceClass(vitrineBlueprint.Object);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	BoxComponent->SetupAttachment(VitrineMeshComponent);
	BoxComponent->SetRelativeLocation(FVector(-70.f, 20.f, 95.f));
	BoxComponent->SetBoxExtent(FVector(13.5f, 16.5f, 10.f));
	BoxComponent->SetRelativeRotation(FRotator(0.f, 151.f, 0.f));
	BoxComponent->bGenerateOverlapEvents = true;
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
		
		if(SpaceSuitActor)
			SpaceSuitActor->InteractableComponent->SetActive(true);	//Doesn't work
	}
}

