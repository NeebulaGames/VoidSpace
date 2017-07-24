// All rights Neebula Games

#include "ProjectMILA.h"
#include "EmergencyModuleActor.h"
#include "LedSwitchComponent.h"

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

	SpotlightComponent = CreateDefaultSubobject<USpotlightComponent>(TEXT("SpotLight"));
	AddOwnedComponent(SpotlightComponent);
}

// Called when the game starts or when spawned
void AEmergencyModuleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEmergencyModuleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

