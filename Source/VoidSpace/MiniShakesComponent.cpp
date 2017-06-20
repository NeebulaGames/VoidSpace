// All rights Neebula Games

#include "VoidSpace.h"
#include "MiniShakesComponent.h"
#include "GameEventManager.h"
#include "SpaceGameStateBase.h"


// Sets default values for this component's properties
UMiniShakesComponent::UMiniShakesComponent() : bIsPlayingMiniShakes(false)
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UMiniShakesComponent::BeginPlay()
{
	Super::BeginPlay();

	playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (playerController)
		GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UMiniShakesComponent::OnOverlap);

	UGameEventManager* manager = ASpaceGameStateBase::Instance(this)->GameEventManager;
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
		GetOwner()->FindComponentByClass<UBoxComponent>()->DestroyComponent();
	}
}

void UMiniShakesComponent::TriggerMiniShake()
{
	if(CameraMiniShakes)
		playerController->ClientPlayCameraShake(CameraMiniShakes, FMath::RandRange(MIN_SHAKE_SCALE, MAX_SHAKE_SCALE));
	
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
		bIsPlayingMiniShakes = true;
	}
	else
	{
		bIsPlayingMiniShakes = false;
	}
}

