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

	CurrentBlinkState = EBlinkLightState::BLINK_TURNING_ON;

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

	if (CurrentState != ELightState::LIGHT_OFF)
	{
		switch (CurrentBlinkState)
		{
		case EBlinkLightState::BLINK_OFF:

			CorridorCentralLight->SetIntensity(0.f);
			MaterialInstanceLeft->SetScalarParameterValue("Color", 0.f);
			MaterialInstanceRight->SetScalarParameterValue("Color", 0.f);
			CurrentColor = 0.f;

			if (Counter >= DelayOFF)
			{
				Counter = DeltaTime;
				DelayOFF = FMath::RandRange(1.3f, 2.5f) + DeltaTime;
				CurrentBlinkState = EBlinkLightState::BLINK_TURNING_ON;
			}
			else
			{
				Counter += DeltaTime;
			}

			break;
		case EBlinkLightState::BLINK_TURNING_ON:

			BlinkLights();

			if (Counter >= DelayON)
			{
				Counter = DeltaTime;
				DelayON = FMath::RandRange(0.1f, 0.5f) + DeltaTime;
				CurrentBlinkState = EBlinkLightState::BLINK_OFF;
			}
			else
			{
				Counter += DeltaTime;
			}
			
			break;
		}
	}
}

void ABlinkLights::BlinkLights()
{
	if (CorridorCentralLight->Intensity != 0.f)
	{
		CorridorCentralLight->SetIntensity(0.f);
	}
	else
	{
		CorridorCentralLight->SetIntensity(LightIntensity);
	}

	if (CurrentColor != 0.f)
	{
		MaterialInstanceLeft->SetScalarParameterValue("Color", 0.f);
		MaterialInstanceRight->SetScalarParameterValue("Color", 0.f);

		CurrentColor = 0.f;
	}
	else
	{
		ChangeLighting(StationManager->LightsState);

		CurrentState == ELightState::LIGHT_EMERGENCY ? CurrentColor = 2.f : CurrentColor = 1.f;
	}	
}

void ABlinkLights::ChangeLighting(ELightState lightState)
{
	float color;

	switch (lightState)
	{
	case ELightState::LIGHT_ON:
		CorridorCentralLight->SetLightColor(LightColor);
		CorridorCentralLight->SetIntensity(LightIntensity);
		color = 1.f;
		break;
	case ELightState::LIGHT_OFF:
		CorridorCentralLight->SetLightColor(LightColor);
		CorridorCentralLight->SetIntensity(0.f);
		color = 0.f;
		break;
	case ELightState::LIGHT_EMERGENCY:
		CorridorCentralLight->SetLightColor(FLinearColor(FColor::Red));
		CorridorCentralLight->SetIntensity(LightIntensity);
		color = 2.f;
		break;
	}

	MaterialInstanceLeft->SetScalarParameterValue("Color", color);
	MaterialInstanceRight->SetScalarParameterValue("Color", color);

	CurrentState = lightState;
}

