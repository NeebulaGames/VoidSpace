// All rights Neebula Games

#include "VoidSpace.h"
#include "LedSwitchComponent.h"
#include "SpaceGameStateBase.h"
#include "SpacestationManagementActor.h"


// Sets default values for this component's properties
ULedSwitchComponent::ULedSwitchComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULedSwitchComponent::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* mesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();

	if (mesh)
	{
		MaterialInstance = mesh->CreateAndSetMaterialInstanceDynamic(0);
	}

	StationManager = ASpaceGameStateBase::Instance(GetWorld())->SpacestationManager;
	CurrentState = StationManager->LedsState;
}


// Called every frame
void ULedSwitchComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentState != StationManager->LedsState && MaterialInstance)
	{
		float blink, color;
		blink = color = 0.f;

		if (StationManager->LedsState == ELedState::LED_EMERGENCY)
			blink = color = 1.f;

		MaterialInstance->SetScalarParameterValue("Color", color);
		MaterialInstance->SetScalarParameterValue("Blink", blink);
	}
}
