// All rights Neebula Games

#include "ProjectMILA.h"
#include <string>
#include "InformativeScreen.h"
#include "SpaceGameStateBase.h"
#include "SpacestationManagementActor.h"


// Sets default values
AInformativeScreen::AInformativeScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> screenMesh(TEXT("StaticMesh'/Game/Meshes/InformativeScreen/InformativeScreen.InformativeScreen'"));
	ScreenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScreenMesh"));

	RootComponent = ScreenMesh;

	ScreenMesh->SetStaticMesh(screenMesh.Object);

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("InformativeText"));

	ConstructorHelpers::FObjectFinder<UFont> textFont(TEXT("Font'/Game/Fonts/DynaGrotesk_LXC_Bold_Font.DynaGrotesk_LXC_Bold_Font'"));
	ConstructorHelpers::FObjectFinder<UMaterial> fontMat(TEXT("Material'/Game/Fonts/M_DynaGrotesk.M_DynaGrotesk'"));

	ConstructorHelpers::FObjectFinder<UMaterial> noSignal(TEXT("Material'/Game/Materials/Props/InformativeScreen/M_NoSignal.M_NoSignal'"));
	ConstructorHelpers::FObjectFinder<UMaterial> statusOK(TEXT("Material'/Game/Materials/Props/InformativeScreen/M_StatusOK.M_StatusOK'"));
	ConstructorHelpers::FObjectFinder<UMaterial> warningMeteo(TEXT("Material'/Game/Materials/Props/InformativeScreen/M_WarningTime.M_WarningTime'"));
	ConstructorHelpers::FObjectFinder<UMaterial> warningOx(TEXT("Material'/Game/Materials/Props/InformativeScreen/M_WarningOx.M_WarningOx'"));

	MaterialNoSignal = noSignal.Object;
	MaterialStatusOK = statusOK.Object;
	MaterialWarningMeteorStorm = warningMeteo.Object;
	MaterialWarningOxygen = warningOx.Object;

	Text->SetRelativeLocation(FVector(17, 6, -26));
	Text->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0, 0, 90)));

	Text->SetupAttachment(RootComponent);

	Text->SetText(FText::AsCultureInvariant("TimeLeft"));
	Text->SetMaterial(0, fontMat.Object);
	Text->SetFont(textFont.Object);
	Text->SetTextRenderColor(FColor::Red);
	Text->SetHorizontalAlignment(EHTA_Center);
}

// Called when the game starts or when spawned
void AInformativeScreen::BeginPlay()
{
	Super::BeginPlay();

	StationManager = ASpaceGameStateBase::Instance(GetWorld())->SpacestationManager;
	
}

// Called every frame
void AInformativeScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (StationManager->ScreensState)
	{
		case EScreenState::SCREEN_NOSIGNAL:
			SetScreenMat(MaterialNoSignal);
			SetTextToScren(FText::GetEmpty());
			break;
		case EScreenState::SCREEN_OK:
			SetScreenMat(MaterialStatusOK);
			SetTextToScren(FText::GetEmpty());
			break;
		case EScreenState::SCREEN_WARNING_METEORITE:
			SetScreenMat(MaterialWarningMeteorStorm);
			SetTextToScren(FText::AsCultureInvariant(StationManager->ScreenMessage));
			break;
		case EScreenState::SCREEN_WARNING_OXYGEN:
			SetScreenMat(MaterialWarningOxygen);
			SetTextToScren(FText::AsCultureInvariant(StationManager->ScreenMessage));
			break;
	}
}

void AInformativeScreen::SetScreenMat(UMaterial* mat)
{
	if (mat != nullptr && mat != ScreenMesh->GetMaterial(1))
		ScreenMesh->SetMaterial(1, mat);
}

void AInformativeScreen::SetTextToScren(FText string)
{
	Text->SetText(string);
}

