// All rights Neebula Games

#include "VoidSpace.h"
#include "InteractableComponent.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent() : bPlayerIsNear(false), TriggerDistance(200)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwner()->GetDistanceTo(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) < TriggerDistance)
	{
		bPlayerIsNear = true;
	}
	else
	{
		bPlayerIsNear = false;
	}
}

void UInteractableComponent::Trigger() const
{
	if (bPlayerIsNear)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Triggered!"));
		OnTriggerAction.Broadcast();
	}
}
