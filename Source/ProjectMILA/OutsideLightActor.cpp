// All rights Neebula Games

#include "ProjectMILA.h"
#include "OutsideLightActor.h"
#include "SpaceGameStateBase.h"


// Sets default values
AOutsideLightActor::AOutsideLightActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> outsideLight(
		TEXT("StaticMesh'/Game/Meshes/Props/OutsideLight/OutsideSpaceLight.OutsideSpaceLight'"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutsideSpaceLight"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetStaticMesh(outsideLight.Object);
}

// Called when the game starts or when spawned
void AOutsideLightActor::BeginPlay()
{
	Super::BeginPlay();

	int index = StaticMeshComponent->GetMaterialIndex("M_SpaceLights");
	MaterialInstance = StaticMeshComponent->CreateAndSetMaterialInstanceDynamic(index);

	GameEventManager = ASpaceGameStateBase::Instance(GetWorld())->GameEventManager;
	GameEventManager->OnEventStarted.AddDynamic(this, &AOutsideLightActor::OnEventStarted);
	
	MaterialInstance->SetScalarParameterValue("Blink", 1.f);
}

void AOutsideLightActor::OnEventStarted()
{
	if (GameEventManager->GetCurrentEvent()->Name.Equals(FString("Breathless")))
	{
		bBlinkLight = false;

		if (!bIsBreachSide)
			MaterialInstance->SetScalarParameterValue("Active", 0.f);
	}
	else if (bBlinkLight == false)
	{
		bBlinkLight = true;

		if(!bIsBreachSide)
			MaterialInstance->SetScalarParameterValue("Active", 1.f);
	}
}
