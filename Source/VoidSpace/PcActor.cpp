// All rights Neebula Games

#include "VoidSpace.h"
#include "PcActor.h"
#include "InteractableComponent.h"
#include "CdAnimInstance.h"
#include "SpaceCharacter.h"


// Sets default values
APcActor::APcActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	InteractableComponent = ObjectInitializer.CreateDefaultSubobject<UInteractableComponent>(this, TEXT("Interactable"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->SetRelativeLocation(FVector(25.f, 20.f, 0.f));
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(20.f, 15.f, 50.f));

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> pcBlueprint(TEXT("AnimBlueprint'/Game/Animations/PC/PcBlueprint.PcBlueprint'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> pc(TEXT("SkeletalMesh'/Game/Meshes/PC/PC.PC'"));
	PcMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PC"));
	PcMeshComponent->SetupAttachment(RootComponent);
	PcMeshComponent->SetSkeletalMesh(pc.Object);
	PcMeshComponent->SetAnimInstanceClass(pcBlueprint.Object->GeneratedClass);
}

// Called when the game starts or when spawned
void APcActor::BeginPlay()
{
	Super::BeginPlay();
	InteractableComponent->OnTriggerEnter.AddDynamic(this, &APcActor::OnEnterCd);
}

void APcActor::OnEnterCd()
{
	ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (character->pickedObject != nullptr && character->pickedObject->GetName().Contains("CD"))
	{
		Cast<UCdAnimInstance>(PcMeshComponent->GetAnimInstance())->bIsInserting = true;
		character->pickedObject->Destroy();
		character->pickedObject = nullptr;
	}
}

