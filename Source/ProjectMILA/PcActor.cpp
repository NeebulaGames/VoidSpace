// All rights Neebula Games

#include "ProjectMILA.h"
#include "PcActor.h"
#include "InteractableComponent.h"
#include "SpaceCharacter.h"
#include "PcAnimInstance.h"
#include "SpaceGameStateBase.h"
#include "GameEventManager.h"
#include "CdActor.h"


// Sets default values
APcActor::APcActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetRelativeLocation(FVector(84.f, -5.f, 0.f));
	BoxComponent->SetBoxExtent(FVector(20.f, 30.f, 14.f));
	BoxComponent->bGenerateOverlapEvents = false;

	static ConstructorHelpers::FObjectFinder<UClass> pcBlueprint(TEXT("Class'/Game/Animations/PC/PcBlueprint.PcBlueprint_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> pc(TEXT("SkeletalMesh'/Game/Meshes/PC/PC.PC'"));
	PcMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PC"));
	PcMeshComponent->SetupAttachment(RootComponent);
	PcMeshComponent->SetSkeletalMesh(pc.Object);
	PcMeshComponent->SetAnimInstanceClass(pcBlueprint.Object);
	PcMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	static ConstructorHelpers::FObjectFinder<USoundWave> cdSound(TEXT("SoundWave'/Game/Sounds/SFX/disk.disk'"));
	InsertCDSound = cdSound.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> cdInserted(TEXT("Material'/Game/Materials/Props/PC/M_CDInserted.M_CDInserted'"));
	M_CDInserted = cdInserted.Object;
}

// Called when the game starts or when spawned
void APcActor::BeginPlay()
{
	Super::BeginPlay();
	ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->OnEventStarted.AddDynamic(this, &APcActor::OnActivePc);
	ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->OnEventFinished.AddDynamic(this, &APcActor::OnDisablePc);
	ScreenMaterial = PcMeshComponent->CreateAndSetMaterialInstanceDynamic(0);
	ScreenMaterial->SetScalarParameterValue("Display", 0.f);
}

void APcActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor->IsA(ACdActor::StaticClass()))
	{
		ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		Cast<UPcAnimInstance>(PcMeshComponent->GetAnimInstance())->bIsInserting = true;
		if(character)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), InsertCDSound, GetActorLocation());
			character->pickedObject->Destroy();
			character->ReleaseObject();
		}
		ASpaceGameStateBase::Instance(GetWorld())->FinishEvent();
	}
}

void APcActor::OnActivePc()
{
	if(ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->GetCurrentEvent()->Name.Equals(FString("The Meteor")))
	{
		ScreenMaterial->SetScalarParameterValue("Display", 1.f);
		BoxComponent->bGenerateOverlapEvents = true;
		bPcIsActive = true;
	}
}

void APcActor::OnDisablePc()
{
	if (bPcIsActive)
	{
		PcMeshComponent->SetMaterial(0, M_CDInserted);
		BoxComponent->bGenerateOverlapEvents = false;
		bPcIsActive = false;
	}
}
