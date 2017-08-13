// All rights Neebula Games

#include "ProjectMILA.h"
#include "LightSwitchComponent.h"
#include "SpaceGameStateBase.h"
#include "SpacestationManagementActor.h"


// Sets default values for this component's properties
ULightSwitchComponent::ULightSwitchComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightSwitchComponent::BeginPlay()
{
	Super::BeginPlay();

	UMeshComponent* mesh = GetOwner()->FindComponentByClass<UMeshComponent>();

	if (mesh)
	{
		int index = mesh->GetMaterialIndex("M_Light");
		MaterialInstance = mesh->CreateAndSetMaterialInstanceDynamic(index);
	}

	StationManager = ASpaceGameStateBase::Instance(GetWorld())->SpacestationManager;
	SetLightState(StationManager->LightsState);
}


// Called every frame
void ULightSwitchComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentState != StationManager->LightsState && MaterialInstance)
	{
		SetLightState(StationManager->LightsState);
	}
}

void ULightSwitchComponent::SetLightState(ELightState state)
{
	float color;

	switch (state)
	{
	case ELightState::LIGHT_OFF:
		color = 0.f;
		break;
	case ELightState::LIGHT_EMERGENCY:
		color = 2.f;
		break;
	case ELightState::LIGHT_ON:
	default:
		color = 1.f;
		break;
	}

	MaterialInstance->SetScalarParameterValue("Color", color);

	CurrentState = state;
}

