// All rights Neebula Games

#include "ProjectMILA.h"
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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> vitrine(TEXT("SkeletalMesh'/Game/Meshes/Vitrine/ExitVaultVitrine.ExitVaultVitrine'"));
	VitrineMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Vitrine"));
	RootComponent = VitrineMeshComponent;
	VitrineMeshComponent->SetSkeletalMesh(vitrine.Object); 
	VitrineMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	static ConstructorHelpers::FObjectFinder<UClass> vitrineBlueprint(TEXT("Class'/Game/Animations/Vitrine/VitrineBlueprint.VitrineBlueprint_C'"));
	VitrineMeshComponent->SetAnimInstanceClass(vitrineBlueprint.Object);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	BoxComponent->SetupAttachment(VitrineMeshComponent);
	BoxComponent->SetRelativeLocation(FVector(-65.f, 50.f, -35.f));
	BoxComponent->SetBoxExtent(FVector(20.f, 19.f, 14.f));
	BoxComponent->bGenerateOverlapEvents = true;

	static ConstructorHelpers::FObjectFinder<USoundWave> vitrineSound(TEXT("SoundWave'/Game/Sounds/SFX/vitrine.vitrine'"));
	OpenVitrineSound = vitrineSound.Object;
}

// Called when the game starts or when spawned
void AVitrineActor::BeginPlay()
{
	Super::BeginPlay();
	ScreenMaterial = VitrineMeshComponent->CreateAndSetMaterialInstanceDynamic(1);
}

void AVitrineActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(AIdCardActor::StaticClass()))
	{
		ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		Cast<UVitrineAnimInstance>(VitrineMeshComponent->GetAnimInstance())->bIsOpening = true;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OpenVitrineSound, GetActorLocation());

		ScreenMaterial->SetScalarParameterValue("Display", 1.f);

		if(character)
		{
			if (character->pickedObject)
			{
				character->pickedObject->Destroy();
				character->ReleaseObject();
			}
			else
			{
				OtherActor->Destroy();
			}
		}
		
		if(SpaceSuitActor)
		{
			SpaceSuitActor->InteractableComponent->SetActive(true);
			SpaceSuitActor->InteractableComponent->bHighlight = true;
		}
	}
}

