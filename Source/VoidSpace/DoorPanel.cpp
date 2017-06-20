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
}

void ADoorPanel::BeginPlay()
{
	Super::BeginPlay();

	if (!ScreenMaterial)
		ScreenMaterial = PanelMesh->CreateAndSetMaterialInstanceDynamic(0);
	ScreenMaterial->SetTextureParameterValue(FName("Screen"), ScreenText);
}

void ADoorPanel::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!ScreenMaterial)
		ScreenMaterial = PanelMesh->CreateAndSetMaterialInstanceDynamic(0);
	ScreenMaterial->SetTextureParameterValue(FName("Screen"), ScreenText);
}

