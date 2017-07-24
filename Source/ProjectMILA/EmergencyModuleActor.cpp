// All rights Neebula Games

#include "ProjectMILA.h"
#include "EmergencyModuleActor.h"
#include "LedSwitchComponent.h"
#include "SpaceGameStateBase.h"

// Sets default values
AEmergencyModuleActor::AEmergencyModuleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> emergencyModule(TEXT("StaticMesh'/Game/Meshes/EmergencyLightModule.EmergencyLightModule'"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EmergencyLightModule"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetStaticMesh(emergencyModule.Object);

	LedSwitchComponent = CreateDefaultSubobject<ULedSwitchComponent>(TEXT("LedSwitch"));
	AddOwnedComponent(LedSwitchComponent);

	SpotlightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotlightComponent->SetupAttachment(RootComponent);
	SpotlightComponent->SetRelativeLocation(FVector(0.f, 10.f, -20.f));
	SpotlightComponent->SetLightColor(FLinearColor(FColor().FromHex(FString("450600FF"))));
	SpotlightComponent->SetIntensity(100000.f);
	SpotlightComponent->SetVisibility(false);
}

// Called when the game starts or when spawned
void AEmergencyModuleActor::BeginPlay()
{
	Super::BeginPlay();
	ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->OnEventStarted.AddDynamic(this, &AEmergencyModuleActor::OnEmergencyStart);
	ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->OnEventFinished.AddDynamic(this, &AEmergencyModuleActor::OnEmergencyFinish);
	SpotlightComponent->SetVisibility(false);
}

// Called every frame
void AEmergencyModuleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isLightOn)
	{
		SpotlightComponent->SetRelativeRotation(FRotator(pitchRotation, 0.f, 0.f));
		pitchRotation += fmod(DeltaTime * 530.f, 360.f);
	}
}

void AEmergencyModuleActor::OnEmergencyStart()
{
	if (ASpaceGameStateBase::Instance(GetWorld())->GameEventManager->GetCurrentEvent()->Name.Equals(FString("The Meteor")))
	{
		SpotlightComponent->ToggleVisibility();
		isLightOn = true;
	}
}

void AEmergencyModuleActor::OnEmergencyFinish()
{
	if (isLightOn)
	{
		SpotlightComponent->ToggleVisibility();
		isLightOn = false;
	}
}


