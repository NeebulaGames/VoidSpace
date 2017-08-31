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

	StationManager = ASpaceGameStateBase::Instance(GetWorld())->SpacestationManager;

	LightIntensity = CorridorCentralLight->Intensity;
	LightColor = CorridorCentralLight->GetLightColor();

	int index = CorridorLeftLight->GetMaterialIndex("M_Light");
	MaterialInstanceLeft = CorridorLeftLight->CreateAndSetMaterialInstanceDynamic(index);

	index = CorridorRightLight->GetMaterialIndex("M_Light");
	MaterialInstanceRight = CorridorRightLight->CreateAndSetMaterialInstanceDynamic(index);

	SwitchState(EBlinkLightState::BLINK_OFF);
	
}

// Called every frame
void ABlinkLights::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentBlinkState)
	{
		case EBlinkLightState::BLINK_OFF:
			StateCounter -= DeltaTime;
			BlinkOff();
			break;
		case EBlinkLightState::BLINK_TURNING_ON:
			StateCounter -= DeltaTime;
			BlinkTurningOn();
			break;
		case EBlinkLightState::BLINK_DISABLED:
			break;
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
			StateCounter = FMath::RandRange(2.f, 2.8f);
			ChangeLighting(ELightState::LIGHT_OFF);
			break;

		case EBlinkLightState::BLINK_TURNING_ON:
			BlinkCounter = FMath::RandRange(1, 3);
			StateCounter = FMath::RandRange(0.2f, 0.4f);
			ChangeLighting(StationManager->LightsState);
			break;

		case EBlinkLightState::BLINK_DISABLED:
			ChangeLighting(ELightState::LIGHT_OFF);
			break;
	}

	CurrentBlinkState = newState;
}

void ABlinkLights::BlinkOff()
{
	if (StationManager->LightsState == ELightState::LIGHT_OFF)
	{
		SwitchState(EBlinkLightState::BLINK_DISABLED);
	}

	if (StateCounter <= 0.f)
	{
		SwitchState(EBlinkLightState::BLINK_TURNING_ON);
	}
}

void ABlinkLights::BlinkTurningOn()
{
	if (StationManager->LightsState == ELightState::LIGHT_OFF)
	{
		SwitchState(EBlinkLightState::BLINK_DISABLED);
	}

	if (BlinkCounter == 0)
	{
		SwitchState(EBlinkLightState::BLINK_OFF);
	}
	else
	{
		if (StateCounter <= 0.f)
		{

			if (CurrentLightState == ELightState::LIGHT_OFF)
			{
				ChangeLighting(StationManager->LightsState);
				StateCounter = FMath::RandRange(0.2f, 0.4f);
			}
			else {
				ChangeLighting(ELightState::LIGHT_OFF);
				StateCounter = FMath::RandRange(0.1f, 0.2f);
				--BlinkCounter;
			}
		}
	}
}
