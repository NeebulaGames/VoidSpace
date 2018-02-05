// All rights Neebula Games

#include "ProjectMILA.h"
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

void UHighlightComponent::OnBeginLooking()
{
	if (bHighlight && ParentMesh)
	{
		ParentMesh->SetRenderCustomDepth(true);
		ParentMesh->SetCustomDepthStencilValue(static_cast<int>(HighlightColor));
	}
}

void UHighlightComponent::OnStopLooking()
{
	if (bHighlight && ParentMesh)
	{
		ParentMesh->SetRenderCustomDepth(false);
		ParentMesh->SetCustomDepthStencilValue(0);
	}
}

