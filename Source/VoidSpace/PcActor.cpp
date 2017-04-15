// All rights Neebula Games

#include "VoidSpace.h"
#include "PcActor.h"
#include "InteractableComponent.h"
#include "CdAnimInstance.h"


// Sets default values
APcActor::APcActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	InteractableComponent = ObjectInitializer.CreateDefaultSubobject<UInteractableComponent>(this, TEXT("Interactable"));
	InteractableComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UClass> pcBlueprint(TEXT("Class'/Game/Animations/PC/PcBlueprint.PcBlueprint_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> pc(TEXT("SkeletalMesh'/Game/Meshes/PC/PC.PC'"));
	PcMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PC"));
	PcMeshComponent->SetupAttachment(RootComponent);
	PcMeshComponent->SetSkeletalMesh(pc.Object);
	PcMeshComponent->SetAnimInstanceClass(pcBlueprint.Object);

}

// Called when the game starts or when spawned
void APcActor::BeginPlay()
{
	Super::BeginPlay();
	InteractableComponent->OnTriggerAction.AddDynamic(this, &APcActor::OnInsertTrigger);
}

void APcActor::OnInsertTrigger()
{
	Cast<UPcAnimInstance>(PcMeshComponent->GetAnimInstance())->bIsInserted = true;
}

