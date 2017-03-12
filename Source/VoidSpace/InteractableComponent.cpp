// All rights Neebula Games

#include "VoidSpace.h"
#include "InteractableComponent.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), bRequireUseButton(true), bPlayerIsNear(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	BoxComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, "TriggerBox");
	BoxComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	BoxComponent->InitBoxExtent(FVector(50));
	BoxComponent->bSelectable = false;
}


// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UInteractableComponent::OnBeginOverlap);
	GetOwner()->OnActorEndOverlap.AddDynamic(this, &UInteractableComponent::OnEndOverlap);
}

void UInteractableComponent::Trigger() const
{
	if (bPlayerIsNear)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Triggered!"));
		OnTriggerAction.Broadcast();
	}
}

void UInteractableComponent::OnBeginOverlap(AActor* actor1, AActor* actor2)
{
	bPlayerIsNear = true;

	if (!bRequireUseButton)
		Trigger();
}

void UInteractableComponent::OnEndOverlap(AActor* actor1, AActor* actor2)
{
	bPlayerIsNear = false;
}