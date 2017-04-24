// All rights Neebula Games

#include "VoidSpace.h"
#include "PcActor.h"
#include "InteractableComponent.h"
#include "SpaceCharacter.h"
#include "PcAnimInstance.h"
#include "SpaceGameStateBase.h"
#include "GameEventManager.h"


// Sets default values
APcActor::APcActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	InteractableComponent = ObjectInitializer.CreateDefaultSubobject<UInteractableComponent>(this, TEXT("Interactable"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->SetRelativeLocation(FVector(60.f, 40.f, 0.f));
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(20.f, 30.f, 9.f));
	InteractableComponent->BoxComponent->bGenerateOverlapEvents = false;

	static ConstructorHelpers::FObjectFinder<UClass> pcBlueprint(TEXT("Class'/Game/Animations/PC/PcBlueprint.PcBlueprint_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> pc(TEXT("SkeletalMesh'/Game/Meshes/PC/PC.PC'"));
	PcMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PC"));
	PcMeshComponent->SetupAttachment(RootComponent);
	PcMeshComponent->SetSkeletalMesh(pc.Object);
	PcMeshComponent->SetAnimInstanceClass(pcBlueprint.Object);
	PcMeshComponent->SetCollisionProfileName(FName("BlockAll"));

	static ConstructorHelpers::FObjectFinder<UMaterial> screenMaterial(TEXT("Material'/Game/Materials/MScreen.MScreen'"));
	if (screenMaterial.Object != NULL)
		ScreenMaterial = (UMaterial*)screenMaterial.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> pcMaterial(TEXT("Material'/Game/Materials/MComputer.MComputer'"));
	if (pcMaterial.Object != NULL)
		PcMaterial = (UMaterial*)pcMaterial.Object;
}

// Called when the game starts or when spawned
void APcActor::BeginPlay()
{
	Super::BeginPlay();
	InteractableComponent->OnTriggerEnter.AddDynamic(this, &APcActor::OnEnterCd);
	ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->OnEventStarted.AddDynamic(this, &APcActor::OnActivePc);
	ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->OnEventFinished.AddDynamic(this, &APcActor::OnDisablePc);
	PcMeshComponent->SetMaterial(1, PcMaterial);
}

void APcActor::OnEnterCd()
{
	ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (character->pickedObject != nullptr && character->pickedObject->GetName().Contains("CD"))
	{
		Cast<UPcAnimInstance>(PcMeshComponent->GetAnimInstance())->bIsInserting = true;
		character->pickedObject->Destroy();
		character->ReleaseObject();
		ASpaceGameStateBase::Instance(GetWorld())->FinishEvent();
	}
}

void APcActor::OnActivePc()
{
	if(ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->GetCurrentEvent()->Name.Equals(FString("The Meteor")))
	{
		PcMeshComponent->SetMaterial(1, ScreenMaterial);
		InteractableComponent->BoxComponent->bGenerateOverlapEvents = true;
		bPcIsActive = true;
	}
}

void APcActor::OnDisablePc()
{
	if (bPcIsActive)
	{
		PcMeshComponent->SetMaterial(1, PcMaterial);
		InteractableComponent->BoxComponent->bGenerateOverlapEvents = true;
		bPcIsActive = false;
	}
}

