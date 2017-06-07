// All rights Neebula Games

#include "VoidSpace.h"
#include "SimonStandActor.h"
#include "PickableComponent.h"
#include "SpaceGameStateBase.h"
#include "GameEventManager.h"
#include "InteractableComponent.h"


// Sets default values
ASimonStandActor::ASimonStandActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> simonStand(TEXT("StaticMesh'/Game/Meshes/Simon/ObservatorySimonStand.ObservatorySimonStand'"));
	SimonStandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SimonStand"));
	SimonStandMesh->SetStaticMesh(simonStand.Object);
	RootComponent = SimonStandMesh;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->SetActive(false);
	InteractableComponent->Deactivate();
	InteractableComponent->BoxComponent->SetRelativeLocation(FVector(0.f, 8.f, 127.f));
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(54.f, 20.f, 20.f));
	InteractableComponent->bRequireUseButton = true;
	InteractableComponent->bRequirePlayerNear = false;
}

// Called when the game starts or when spawned
void ASimonStandActor::BeginPlay()
{
	Super::BeginPlay();

	UGameEventManager* manager = ASpaceGameStateBase::Instance(this)->GameEventManager;
	manager->OnEventStarted.AddDynamic(this, &ASimonStandActor::EventStarted);
	manager->OnEventFinished.AddDynamic(this, &ASimonStandActor::EventFinished);

	InteractableComponent->OnTriggerAction.AddDynamic(this, &ASimonStandActor::SimonCompleted);
}

void ASimonStandActor::SimonCompleted()
{
	bSimonCompleted = true;
	OnSimonCompleted.Broadcast();
}

void ASimonStandActor::EventStarted()
{
	if (ASpaceGameStateBase::Instance(this)->GameEventManager->GetCurrentEvent()->Name != "Beginning" && !bSimonCompleted)
	{
		SimonStandMesh->bGenerateOverlapEvents = false;
		SimonCompleted();
	}
	else 
	{
		SimonStandMesh->bGenerateOverlapEvents = ASpaceGameStateBase::Instance(this)->GameEventManager->GetCurrentEvent()->Name == "Beginning";
	}
}

void ASimonStandActor::EventFinished()
{
	if (ASpaceGameStateBase::Instance(this)->GameEventManager->GetCurrentEvent()->Name == "Beginning" && !bSimonCompleted)
	{
		SimonStandMesh->bGenerateOverlapEvents = false;
		SimonCompleted();
	}
}
