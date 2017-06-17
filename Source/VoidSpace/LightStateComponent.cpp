// All rights Neebula Games

#include "VoidSpace.h"
#include "LightStateComponent.h"
#include "SpaceGameStateBase.h"
#include "SpacestationManagementActor.h"

// Sets default values for this component's properties
ULightStateComponent::ULightStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void ULightStateComponent::BeginPlay()
{
	Super::BeginPlay();

	ParentLight = GetOwner()->FindComponentByClass<ULightComponent>();
	StationManager = ASpaceGameStateBase::Instance(GetWorld())->SpacestationManager;
	
	ChangeLighting(StationManager->LightsState);
}

void ULightStateComponent::ChangeLighting(ELightState lightState)
{	
	switch (lightState)
	{
	case ELightState::LIGHT_ON:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ON"));
		ParentLight->SetLightColor(FLinearColor(FColor::White));
		ParentLight->SetIntensity(5000.0f);
		break;
	case ELightState::LIGHT_OFF:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("OFF"));
		ParentLight->SetLightColor(FLinearColor(FColor::White));
		ParentLight->SetIntensity(0.f);
		break;
	case ELightState::LIGHT_EMERGENCY:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Emergency"));
		ParentLight->SetLightColor(FLinearColor(FColor::Red));
		ParentLight->SetIntensity(5000.0f);
		break;
	}

	CurrentState = lightState;
}


// Called every frame
void ULightStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentState != StationManager->LightsState)
		ChangeLighting(StationManager->LightsState);
}

