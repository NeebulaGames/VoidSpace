// All rights Neebula Games

#include "ProjectMILA.h"
#include "SpaceSuitActor.h"
#include "InteractableComponent.h"
#include "SpaceGameStateBase.h"
#include "GameEventManager.h"
#include "SpaceCharacter.h"


// Sets default values
ASpaceSuitActor::ASpaceSuitActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	OxygenDelta = 100.f / OxygenTime;
}

void ASpaceSuitActor::Tick(float DeltaSeconds)
{
	if (bCountingDown)
	{
		TimeRemaining -= DeltaSeconds;

		if (TimeRemaining <= 0.f && GameEventManager->GetCurrentEvent()->DeathReason != EDeathReason::Choke)
		{
			bCountingDown = false;
			GameEventManager->SetTime(0.f, false); // Stop counter for safety
			ASpaceGameStateBase::Instance(GetWorld())->Die(GameEventManager->GetCurrentEvent()->DeathReason);
		}
	}
}

void ASpaceSuitActor::StartConsumingOxygen()
{
	if (!bConsumingOxygen)
	{
		bCountingDown = GameEventManager->IsCounting();
		TimeRemaining = GameEventManager->GetTime();

		GameEventManager->OnEventStarted.AddDynamic(this, &ASpaceSuitActor::OnEventStarted);
		GameEventManager->OnEventFinished.AddDynamic(this, &ASpaceSuitActor::OnEventFinished);

		GameEventManager->SetTime(OxygenTime, true);
	}

	bConsumingOxygen = true;
}

void ASpaceSuitActor::StopConsumingOxygen()
{
	OxygenTime = GameEventManager->GetTime();
	GameEventManager->SetTime(TimeRemaining, bCountingDown);

	GameEventManager->OnEventStarted.RemoveDynamic(this, &ASpaceSuitActor::OnEventStarted);
	GameEventManager->OnEventFinished.RemoveDynamic(this, &ASpaceSuitActor::OnEventFinished);

	bConsumingOxygen = false;
}

float ASpaceSuitActor::GetRemainingOxygen() const
{
	if (bActive && bConsumingOxygen)
		return GameEventManager->GetTime();
	return OxygenTime;
}

bool ASpaceSuitActor::IsConsumingOxygen() const
{
	return bConsumingOxygen;
}

// Called when the game starts or when spawned
void ASpaceSuitActor::BeginPlay()
{
	Super::BeginPlay();

	InteractableComponent->OnTriggerAction.AddDynamic(this, &ASpaceSuitActor::OnSuitTrigger);

	GameEventManager = ASpaceGameStateBase::Instance(GetWorld())->GameEventManager;
}

void ASpaceSuitActor::OnSuitTrigger()
{
	float delay = 1.0f;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0.f, 1.f, delay, FLinearColor::Black, false, true);

	ASpaceGameStateBase* state = ASpaceGameStateBase::Instance(GetWorld());
	state->DisablePlayerInput();
	state->bInteractionAllowed = false;

	static FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(unusedHandle, this, &ASpaceSuitActor::OnFadeOutFinish, delay);
}

void ASpaceSuitActor::OnFadeOutFinish()
{
	ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	bActive = !bActive;

	if (character)
	{
		character->ToggleSpaceSuit(bActive ? this : nullptr);
	}

	UGameplayStatics::PlaySound2D(GetWorld(), Zipper);

	SpaceSuitComponent->ToggleVisibility();
	SpaceSuitComponent->ToggleActive();

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
	state->EnablePlayerInput();
	state->bInteractionAllowed = true;
}

void ASpaceSuitActor::OnEventStarted()
{
	bCountingDown = GameEventManager->IsCounting();
	TimeRemaining = GameEventManager->GetTime();

	GameEventManager->SetTime(OxygenTime, true);
}

void ASpaceSuitActor::OnEventFinished()
{
	OxygenTime = GameEventManager->GetTime();
}
