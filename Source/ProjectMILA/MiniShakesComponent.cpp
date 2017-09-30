// All rights Neebula Games

#include "ProjectMILA.h"
#include "MiniShakesComponent.h"
#include "GameEventManager.h"
#include "SpaceGameStateBase.h"


// Sets default values for this component's properties
UMiniShakesComponent::UMiniShakesComponent() : bIsPlayingMiniShakes(false)
{
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USoundWave> shakeSound(TEXT("SoundWave'/Game/Sounds/SFX/shaking.shaking'"));
	ShakeSound = shakeSound.Object;
}

// Called when the game starts
void UMiniShakesComponent::BeginPlay()
{
	Super::BeginPlay();

	playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (playerController)
		GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UMiniShakesComponent::OnOverlap);

	ASpaceGameStateBase* gameState = ASpaceGameStateBase::Instance(this);

	gameState->OnPlayerDead.AddDynamic(this, &UMiniShakesComponent::StopMiniShakes);

	UGameEventManager* manager = gameState->GameEventManager;
	manager->OnEventStarted.AddDynamic(this, &UMiniShakesComponent::StartMiniShakes);
}

void UMiniShakesComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(MiniShakeTimerHandle);
}

void UMiniShakesComponent::OnOverlap(AActor* actor1, AActor* actor2)
{
	if (actor2 == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		bIsPlayingMiniShakes = true;
		TriggerMiniShakeWithDelay(0.1f);

		for (int32 i = 0; i < meteoriteParticleSystems.Num(); ++i)
			meteoriteParticleSystems[i]->StartEmission();

		GetOwner()->FindComponentByClass<UBoxComponent>()->DestroyComponent();
	}
}

void UMiniShakesComponent::TriggerMiniShake()
{
	if (CameraMiniShakes) {
		playerController->ClientPlayCameraShake(CameraMiniShakes, FMath::RandRange(MIN_SHAKE_SCALE, MAX_SHAKE_SCALE));
		UGameplayStatics::PlaySound2D(GetWorld(), ShakeSound);
	}
	
	if(bIsPlayingMiniShakes)
		TriggerMiniShakeWithDelay(FMath::RandRange(MIN_SHAKE_DELAY, MAX_SHAKE_DELAY));
}

void UMiniShakesComponent::TriggerMiniShakeWithDelay(float seconds)
{
	GetWorld()->GetTimerManager().SetTimer(MiniShakeTimerHandle, this, &UMiniShakesComponent::TriggerMiniShake, seconds);
}

void UMiniShakesComponent::StartMiniShakes()
{
	if (ASpaceGameStateBase::Instance(this)->GameEventManager->GetCurrentEvent()->Name.Contains("The Meteor") && !bIsPlayingMiniShakes)
	{
		TriggerMiniShakeWithDelay(FMath::RandRange(MIN_SHAKE_DELAY, MAX_SHAKE_DELAY));

		for (int32 i = 0; i < meteoriteParticleSystems.Num(); ++i)
			meteoriteParticleSystems[i]->StartEmission();

		bIsPlayingMiniShakes = true;
	}
	else
	{
		bIsPlayingMiniShakes = false;
	}
}

void UMiniShakesComponent::StopMiniShakes()
{
	GetWorld()->GetTimerManager().ClearTimer(MiniShakeTimerHandle);

	bIsPlayingMiniShakes = false;
}

