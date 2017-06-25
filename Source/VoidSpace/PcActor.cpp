// All rights Neebula Games

#include "VoidSpace.h"
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

	static ConstructorHelpers::FObjectFinder<UClass> pcBlueprint(TEXT("Class'/Game/Animations/PC2/PcBlueprint.PcBlueprint_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> pc(TEXT("SkeletalMesh'/Game/Meshes/PC2/PC.PC'"));
	PcMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PC"));
	PcMeshComponent->SetupAttachment(RootComponent);
	PcMeshComponent->SetSkeletalMesh(pc.Object);
	PcMeshComponent->SetAnimInstanceClass(pcBlueprint.Object);
	PcMeshComponent->SetCollisionProfileName(FName("BlockAll"));
}

// Called when the game starts or when spawned
void APcActor::BeginPlay()
{
	Super::BeginPlay();
	ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->OnEventStarted.AddDynamic(this, &APcActor::OnActivePc);
	ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->OnEventFinished.AddDynamic(this, &APcActor::OnDisablePc);
	ScreenMaterial = PcMeshComponent->CreateAndSetMaterialInstanceDynamic(6);
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
		ScreenMaterial->SetScalarParameterValue("Display", 0.f);
		BoxComponent->bGenerateOverlapEvents = false;
		bPcIsActive = false;
	}
}

