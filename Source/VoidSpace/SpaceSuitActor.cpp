// All rights Neebula Games

#include "VoidSpace.h"
#include "SpaceSuitActor.h"
#include "InteractableComponent.h"
#include "SpaceGameStateBase.h"


// Sets default values
ASpaceSuitActor::ASpaceSuitActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = root;

	InteractableComponent = ObjectInitializer.CreateDefaultSubobject<UInteractableComponent>(this, TEXT("Interactable"));
	InteractableComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> spaceSuit(TEXT("StaticMesh'/Game/Meshes/SpaceSuit.SpaceSuit'"));
	SpaceSuitComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("SpaceSuit"));
	SpaceSuitComponent->SetupAttachment(RootComponent);
	SpaceSuitComponent->SetStaticMesh(spaceSuit.Object);

	static ConstructorHelpers::FObjectFinder<USoundWave> zipperSound(TEXT("SoundWave'/Game/Sounds/zipper.zipper'"));
	Zipper = zipperSound.Object;
}

// Called when the game starts or when spawned
void ASpaceSuitActor::BeginPlay()
{
	Super::BeginPlay();

	InteractableComponent->OnTriggerAction.AddDynamic(this, &ASpaceSuitActor::OnSuitTrigger);
}

void ASpaceSuitActor::OnSuitTrigger()
{
	float delay = 1.0f;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0.f, 1.f, delay, FLinearColor::Black, false, true);

	ASpaceGameStateBase* state = ASpaceGameStateBase::Instance(GetWorld());
	state->bMovementAllowed = false;
	state->bInteractionAllowed = false;

	static FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(unusedHandle, this, &ASpaceSuitActor::OnFadeOutFinish, delay);
}

void ASpaceSuitActor::OnFadeOutFinish()
{
	ASpaceGameStateBase* state = ASpaceGameStateBase::Instance(GetWorld());

	UGameplayStatics::PlaySound2D(GetWorld(), Zipper);

	SpaceSuitComponent->ToggleVisibility();
	SpaceSuitComponent->ToggleActive();
	state->ToggleSpaceSuit(!SpaceSuitComponent->IsVisible());

	static FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(unusedHandle, this, &ASpaceSuitActor::OnSoundFinished, Zipper->Duration);
}

void ASpaceSuitActor::OnSoundFinished()
{
	float delay = 1.0f;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1.f, 0.f, delay, FLinearColor::Black);

	static FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(unusedHandle, this, &ASpaceSuitActor::OnFadeInFinished, delay);
}

void ASpaceSuitActor::OnFadeInFinished()
{
	ASpaceGameStateBase* state = ASpaceGameStateBase::Instance(GetWorld());
	state->bMovementAllowed = true;
	state->bInteractionAllowed = true;
}
