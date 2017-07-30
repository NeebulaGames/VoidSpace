// All rights Neebula Games

#include "ProjectMILA.h"
#include "EmergencyModuleActor.h"
#include "LedSwitchComponent.h"
#include "SpaceGameStateBase.h"
#include "SpacestationManagementActor.h"

// Sets default values
AEmergencyModuleActor::AEmergencyModuleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> emergencyModule(TEXT("StaticMesh'/Game/Meshes/Props/EmergencyModule/EmergencyLightModule.EmergencyLightModule'"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EmergencyLightModule"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetStaticMesh(emergencyModule.Object);

	LedSwitchComponent = CreateDefaultSubobject<ULedSwitchComponent>(TEXT("LedSwitch"));
	AddOwnedComponent(LedSwitchComponent);

	SpotlightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotlightComponent->SetupAttachment(RootComponent);
	SpotlightComponent->SetRelativeLocation(FVector(0.f, 20.f, -20.f));
	SpotlightComponent->SetLightColor(FLinearColor(FColor().FromHex(FString("450600FF"))));
	SpotlightComponent->SetIntensity(100000.f);
	SpotlightComponent->SetVisibility(false);
}

// Called when the game starts or when spawned
void AEmergencyModuleActor::BeginPlay()
{
	Super::BeginPlay();
	SpotlightComponent->SetVisibility(false);
	StationManager = ASpaceGameStateBase::Instance(GetWorld())->SpacestationManager;
}

// Called every frame
void AEmergencyModuleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ELightState::LIGHT_EMERGENCY == StationManager->LightsState)
	{
		SpotlightComponent->SetVisibility(true);
		SpotlightComponent->SetRelativeRotation(FRotator(pitchRotation, 0.f, 0.f));
		pitchRotation += fmod(DeltaTime * 530.f, 360.f);
	}else
	{
		SpotlightComponent->SetVisibility(false);
	}
}
