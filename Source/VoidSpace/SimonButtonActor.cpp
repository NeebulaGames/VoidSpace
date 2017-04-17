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
	RootComponent = SimonButtonMesh;
	SimonButtonMesh->SetStaticMesh(simonButton.Object);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(RootComponent);
	InteractableComponent->SetActive(false);
	InteractableComponent->Deactivate();
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(10.f, 7.f, 5.f));
	InteractableComponent->bRequireUseButton = true;
}

void ASimonButtonActor::SetColor(const FLinearColor& color, float blink) const
{
	ButtonMaterial->SetScalarParameterValue("Blink", blink);
	ButtonMaterial->SetVectorParameterValue("Color", color);
}

void ASimonButtonActor::TurnOn()
{
	GetWorldTimerManager().ClearTimer(PressHandle); // Bug
	ButtonMaterial->SetScalarParameterValue("On", 1.f);
}

void ASimonButtonActor::TurnOff()
{
	ButtonMaterial->SetScalarParameterValue("On", 0.f);
}

// Called when the game starts or when spawned
void ASimonButtonActor::BeginPlay()
{
	Super::BeginPlay();
	ButtonMaterial = SimonButtonMesh->CreateAndSetMaterialInstanceDynamic(0);

	ButtonMaterial->SetScalarParameterValue("Blink", 1.f);

	InteractableComponent->OnTriggerAction.AddDynamic(this, &ASimonButtonActor::ButtonClicked);

	GetWorldTimerManager().SetTimer(PressHandle, -1.f, false);
}

void ASimonButtonActor::ButtonClicked()
{
	OnButtonClicked.Broadcast(ButtonNumber);

	ButtonMaterial->SetScalarParameterValue("On", 1.f);
	GetWorldTimerManager().SetTimer(PressHandle, this, &ASimonButtonActor::TurnOff, 1.f, false);
}
