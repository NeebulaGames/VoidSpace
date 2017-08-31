// All rights Neebula Games

#include "ProjectMILA.h"
#include "BlinkLights.h"
#include "SpaceGameStateBase.h"
#include "SpacestationManagementActor.h"


// Sets default values
ABlinkLights::ABlinkLights()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> corridorUpperLight(TEXT("StaticMesh'/Game/Meshes/Props/Lights/PanelCorridorLight/PanelCorridorLight.PanelCorridorLight'"));

	CorridorLeftLight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftLight"));
	CorridorLeftLight->SetStaticMesh(corridorUpperLight.Object);
	CorridorLeftLight->SetupAttachment(RootComponent);

	CorridorRightLight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightLight"));
	CorridorRightLight->SetStaticMesh(corridorUpperLight.Object);
	CorridorRightLight->SetupAttachment(RootComponent);

	CorridorCentralLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("CentralLight"));
	CorridorCentralLight->SetIntensity(1100.f);
	CorridorCentralLight->SetAttenuationRadius(500.f);
	CorridorCentralLight->SetLightColor(FLinearColor(255.f,255.f,255.f));

}

// Called when the game starts or when spawned
void ABlinkLights::BeginPlay()
{
	Super::BeginPlay();

	SwitchState(EBlinkLightState::BLINK_OFF);

	StationManager = ASpaceGameStateBase::Instance(GetWorld())->SpacestationManager;

	LightIntensity = CorridorCentralLight->Intensity;
	LightColor = CorridorCentralLight->GetLightColor();

	int index = CorridorLeftLight->GetMaterialIndex("M_Light");
	MaterialInstanceLeft = CorridorLeftLight->CreateAndSetMaterialInstanceDynamic(index);

	index = CorridorRightLight->GetMaterialIndex("M_Light");
	MaterialInstanceRight = CorridorRightLight->CreateAndSetMaterialInstanceDynamic(index);

	ChangeLighting(StationManager->LightsState);
	
}

// Called every frame
void ABlinkLights::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentBlinkState)
	{
		case EBlinkLightState::BLINK_OFF:
			BlinkOff();
			break;
		case EBlinkLightState::BLINK_TURNING_ON:
			BlinkTurningOn();
			break;
		case EBlinkLightState::BLINK_DISABLED:
			break;
	}
}

void ABlinkLights::BlinkLights()
{
	// Light [Central] && LEDs [sides]
	if (CorridorCentralLight->Intensity != 0.f && CurrentColor != 0.f)
	{
		CorridorCentralLight->SetIntensity(0.f);

		MaterialInstanceLeft->SetScalarParameterValue("Color", 0.f);
		MaterialInstanceRight->SetScalarParameterValue("Color", 0.f);

		CurrentColor = 0.f;
	}
	else
	{
		ChangeLighting(StationManager->LightsState);
	}
}

void ABlinkLights::ChangeLighting(ELightState lightState)
{
	switch (lightState)
	{
	case ELightState::LIGHT_ON:
		CorridorCentralLight->SetLightColor(LightColor);
		CorridorCentralLight->SetIntensity(LightIntensity);
		CurrentColor = 1.f;
		break;
	case ELightState::LIGHT_OFF:
		CorridorCentralLight->SetLightColor(LightColor);
		CorridorCentralLight->SetIntensity(0.f);
		CurrentColor = 0.f;
		break;
	case ELightState::LIGHT_EMERGENCY:
		CorridorCentralLight->SetLightColor(FLinearColor(FColor::Red));
		CorridorCentralLight->SetIntensity(LightIntensity);
		CurrentColor = 2.f;
		break;
	}

	MaterialInstanceLeft->SetScalarParameterValue("Color", CurrentColor);
	MaterialInstanceRight->SetScalarParameterValue("Color", CurrentColor);

	CurrentLightState = lightState;
}

void ABlinkLights::SwitchState(EBlinkLightState newState)
{
	switch (newState)
	{
		case EBlinkLightState::BLINK_OFF:
			SetBlinkDisabled();
			break;

		case EBlinkLightState::BLINK_TURNING_ON:
			ChangeLighting(StationManager->LightsState);
			break;

		case EBlinkLightState::BLINK_DISABLED:
			SetBlinkDisabled();
			break;
	}

	CurrentBlinkState = newState;
}

void ABlinkLights::BlinkOff()
{
	if(StationManager->LightsState == ELightState::LIGHT_OFF)
	{
		SwitchState(EBlinkLightState::BLINK_DISABLED);
	}

	//TODO: wait some random time

	SwitchState(EBlinkLightState::BLINK_TURNING_ON);

}

void ABlinkLights::BlinkTurningOn()
{
	if (StationManager->LightsState == ELightState::LIGHT_OFF)
	{
		SwitchState(EBlinkLightState::BLINK_DISABLED);
	}

	//TODO: do blinking stuff (between 1-3 blinks (random time between them) )

	SwitchState(EBlinkLightState::BLINK_OFF);
}

void ABlinkLights::SetBlinkDisabled()
{
	CorridorCentralLight->SetIntensity(0.f);

	MaterialInstanceLeft->SetScalarParameterValue("Color", 0.f);
	MaterialInstanceRight->SetScalarParameterValue("Color", 0.f);

	CurrentColor = 0.f;
}
