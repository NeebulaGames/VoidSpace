// All rights Neebula Games

#include "VoidSpace.h"
#include "InteractableComponent.h"
#include "SpaceCharacter.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer), bRequirePlayerNear(true), bRequireUseButton(true), bPlayerIsNear(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	BoxComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, "TriggerBox");
	BoxComponent->SetupAttachment(this);
	BoxComponent->InitBoxExtent(FVector(50));
	BoxComponent->bSelectable = false;

	bAutoActivate = true;
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
	if ((!bRequirePlayerNear || bPlayerIsNear) && bRequireUseButton)
	{
		OnTriggerAction.Broadcast();
	}
}

void UInteractableComponent::OnBeginOverlap(AActor* actor1, AActor* actor2)
{
	if (actor2->IsA(ASpaceCharacter::StaticClass()))
	{
		bPlayerIsNear = true;
		
		//if (IsActive()) // TODO: Enable me when map can be edited
		    OnTriggerEnter.Broadcast();
	}
}

void UInteractableComponent::OnEndOverlap(AActor* actor1, AActor* actor2)
{
	if (actor2->IsA(ASpaceCharacter::StaticClass()))
	{
		bPlayerIsNear = false;
		
		//if (IsActive()) // TODO: Enable me when map can be edited
		    OnTriggerExit.Broadcast();
	}
}
