// All rights Neebula Games

#include "ProjectMILA.h"
#include "SimonStandActor.h"
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
	InteractableComponent->BoxComponent->SetRelativeLocation(FVector(0.f, 8.f, 127.f));
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(54.f, 20.f, 20.f));

	static ConstructorHelpers::FObjectFinder<ULevelSequence> meteorStorm(TEXT("LevelSequence'/Game/Sequences/MeteoritesSequence.MeteoritesSequence'"));
	MeteorStorm = meteorStorm.Object;
}

// Called when the game starts or when spawned
void ASimonStandActor::BeginPlay()
{
	Super::BeginPlay();

	UGameEventManager* manager = ASpaceGameStateBase::Instance(this)->GameEventManager;
	manager->OnEventStarted.AddDynamic(this, &ASimonStandActor::EventStarted);

	InteractableComponent->OnTriggerAction.AddDynamic(this, &ASimonStandActor::SimonCompleted);
	ScreenMaterial = SimonStandMesh->CreateAndSetMaterialInstanceDynamic(1);

	
}

void ASimonStandActor::SimonCompleted()
{
	InteractableComponent->DestroyComponent();
	ScreenMaterial->SetScalarParameterValue("Display", 1.f);
	OnSimonCompleted.Broadcast();

	//call meteor sequence
	if (!bSimonCompleted && ASpaceGameStateBase::Instance(this)->GameEventManager->GetCurrentEvent()->Name == "Beginning")
	{
		ASpaceGameStateBase* state = ASpaceGameStateBase::Instance(GetWorld());

		FMovieSceneSequencePlaybackSettings settings;
		ALevelSequenceActor* outActor;
		ULevelSequencePlayer* player = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), MeteorStorm, settings, outActor);
		player->SetPlaybackPosition(0.f);
		player->Play();
		
		FTimerHandle unused;
		FTimerDelegate callback;
		callback.BindLambda([this, state]() -> void {state->FinishEvent(); });
		GetWorldTimerManager().SetTimer(unused, callback, player->GetLength(), false);
	}

	bSimonCompleted = true;
}

void ASimonStandActor::EventStarted()
{
	if (ASpaceGameStateBase::Instance(this)->GameEventManager->GetCurrentEvent()->Name != "Beginning" && !bSimonCompleted)
		SimonCompleted();
}
