// All rights Neebula Games

#include "VoidSpace.h"
#include "DoorPanel.h"


// Sets default values
ADoorPanel::ADoorPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> panelMesh(TEXT("StaticMesh'/Game/Meshes/DoorPanel/DoorsPanel.DoorsPanel'"));
	PanelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PanelMesh"));

	RootComponent = PanelMesh;

	PanelMesh->SetStaticMesh(panelMesh.Object);

	ConstructorHelpers::FObjectFinder<UMaterial> bedroom(TEXT("Material'/Game/Materials/Props/DoorPanel/M_Bedroom.M_Bedroom'"));
	ConstructorHelpers::FObjectFinder<UMaterial> exitVault(TEXT("Material'/Game/Materials/Props/DoorPanel/M_ExitValt.M_ExitValt'"));
	ConstructorHelpers::FObjectFinder<UMaterial> maintenance(TEXT("Material'/Game/Materials/Props/DoorPanel/M_Maintenance.M_Maintenance'"));
	ConstructorHelpers::FObjectFinder<UMaterial> observatory(TEXT("Material'/Game/Materials/Props/DoorPanel/M_Observatory.M_Observatory'"));
	ConstructorHelpers::FObjectFinder<UMaterial> controlRoom(TEXT("Material'/Game/Materials/Props/DoorPanel/M_ControlRoom.M_ControlRoom'"));

	MaterialBedroom = bedroom.Object;
	MaterialExitVault = exitVault.Object;
	MaterialMaintenance = maintenance.Object;
	MaterialObservatory = observatory.Object;
	MaterialControlRoom = controlRoom.Object;

}

// Called when the game starts or when spawned
void ADoorPanel::BeginPlay()
{
	Super::BeginPlay();

	switch (PanelModuleText)
	{
	case PanelModule::PANEL_BEDROOM:
		PanelMesh->SetMaterial(0, MaterialBedroom);
		break;
	case PanelModule::PANEL_EXITVAULT:
		PanelMesh->SetMaterial(0, MaterialExitVault);
		break;
	case PanelModule::PANEL_MAINTENANCE:
		PanelMesh->SetMaterial(0, MaterialMaintenance);
		break;
	case PanelModule::PANEL_OBSERVATORY:
		PanelMesh->SetMaterial(0, MaterialObservatory);
		break;
	case PanelModule::PANEL_CONTROLROOM:
		PanelMesh->SetMaterial(0, MaterialControlRoom);
		break;
	}
	
}

// Called every frame
void ADoorPanel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

