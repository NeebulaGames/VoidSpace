// All rights Neebula Games

#include "VoidSpace.h"
#include "MessageTriggerActor.h"
#include "InteractableComponent.h"


// Sets default values
AMessageTriggerActor::AMessageTriggerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable Component"));
	RootComponent = InteractableComponent;
	InteractableComponent->bRequireUseButton = false;
	InteractableComponent->BoxComponent->SetBoxExtent(FVector(10.f, 10.f, 10));

	bOneShot = true;
	DisplayTime = 2.f;
	DisplayColor = FColor::Green;
}

// Called when the game starts or when spawned
void AMessageTriggerActor::BeginPlay()
{
	Super::BeginPlay();

	InteractableComponent->OnTriggerEnter.AddDynamic(this, &AMessageTriggerActor::OnTriggerEnter);
}

void AMessageTriggerActor::OnTriggerEnter()
{
	if (bOneShot)
		InteractableComponent->OnTriggerEnter.RemoveDynamic(this, &AMessageTriggerActor::OnTriggerEnter);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, DisplayTime, DisplayColor, DisplayText);
}
