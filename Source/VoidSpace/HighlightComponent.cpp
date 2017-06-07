// All rights Neebula Games

#include "VoidSpace.h"
#include "HighlightComponent.h"


// Sets default values for this component's properties
UHighlightComponent::UHighlightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

UHighlightComponent::UHighlightComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


// Called when the game starts
void UHighlightComponent::BeginPlay()
{
	Super::BeginPlay();

	ParentMesh = GetOwner()->FindComponentByClass<UMeshComponent>();
}


// Called every frame
void UHighlightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHighlightComponent::OnBeginLooking()
{
	if (bHighlight && ParentMesh)
	{
		ParentMesh->SetRenderCustomDepth(true);
		ParentMesh->CustomDepthStencilValue = STENCIL_ITEMHIGHLIGHT;
	}
}

void UHighlightComponent::OnStopLooking()
{
	if (bHighlight && ParentMesh)
	{
		ParentMesh->SetRenderCustomDepth(false);
		ParentMesh->CustomDepthStencilValue = 0;
	}
}

