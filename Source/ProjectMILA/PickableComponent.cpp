// All rights Neebula Games

#include "ProjectMILA.h"
#include "PickableComponent.h"


// Sets default values for this component's properties
UPickableComponent::UPickableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPickableComponent::BeginPlay()
{
	Super::BeginPlay();

	ParentMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	// ...
	
}


// Called every frame
void UPickableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

