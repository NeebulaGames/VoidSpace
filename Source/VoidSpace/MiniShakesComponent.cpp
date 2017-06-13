// All rights Neebula Games

#include "VoidSpace.h"
#include "MiniShakesComponent.h"
#include "GameEventManager.h"
#include "SpaceGameStateBase.h"


// Sets default values for this component's properties
UMiniShakesComponent::UMiniShakesComponent() : bIsPlayingMiniShakes(false)
{
	PrimaryComponentTick.bCanEverTick = true;
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
	manager->OnEventFinished.AddDynamic(this, &UMiniShakesComponent::StopMiniShakes);
}

void UMiniShakesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsPlayingMiniShakes && GetWorld()->GetTimerManager().GetTimerRemaining(MiniShakeTimerHandle) <= 0.f)
		TriggerMiniShakeWithDelay(FMath::RandRange(MIN_SHAKE_DELAY, MAX_SHAKE_DELAY));
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
		TriggerMiniShakeWithDelay(0.f);
		GetOwner()->FindComponentByClass<UBoxComponent>()->bGenerateOverlapEvents = false;
	}
}

void UMiniShakesComponent::TriggerMiniShake()
{
	if(CameraMiniShakes)
		playerController->ClientPlayCameraShake(CameraMiniShakes, FMath::RandRange(MIN_SHAKE_SCALE, MAX_SHAKE_SCALE));
}

void UMiniShakesComponent::TriggerMiniShakeWithDelay(float seconds)
{
	GetWorld()->GetTimerManager().SetTimer(MiniShakeTimerHandle, this, &UMiniShakesComponent::TriggerMiniShake, seconds);
}

void UMiniShakesComponent::StopMiniShakes()
{
	if(ASpaceGameStateBase::Instance(this)->GameEventManager->GetCurrentEvent()->Name.Contains("The Meteor") && bIsPlayingMiniShakes)
		bIsPlayingMiniShakes = false;
}

void UMiniShakesComponent::StartMiniShakes()
{
	if (ASpaceGameStateBase::Instance(this)->GameEventManager->GetCurrentEvent()->Name.Contains("The Meteor") && !bIsPlayingMiniShakes)
		bIsPlayingMiniShakes = true;
}

