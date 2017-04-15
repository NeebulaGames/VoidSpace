// All rights Neebula Games

#include "VoidSpace.h"
#include "SimonButtonActor.h"
#include "InteractableComponent.h"


// Sets default values
ASimonButtonActor::ASimonButtonActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> simonButton(TEXT("StaticMesh'/Game/Meshes/Simon/Simon_Piece.Simon_Piece'"));
	SimonButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SimonButton"));
	SimonButtonMesh->SetupAttachment(RootComponent);
	SimonButtonMesh->SetStaticMesh(simonButton.Object);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->SetActive(false);
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(10.f, 7.f, 5.f));
}

// Called when the game starts or when spawned
void ASimonButtonActor::BeginPlay()
{
	Super::BeginPlay();
	ButtonMaterial = SimonButtonMesh->CreateAndSetMaterialInstanceDynamic(0);

	ButtonMaterial->SetScalarParameterValue("Blink", 1.f);
}
