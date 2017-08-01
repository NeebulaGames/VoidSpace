// All rights Neebula Games

#include "ProjectMILA.h"
#include "DialogueTriggerComponent.h"
#include "SpaceCharacter.h"
#include "InteractableComponent.h"
#include "SpaceGameStateBase.h"
#include "DialogueManager.h"

// Sets default values for this component's properties
UDialogueTriggerComponent::UDialogueTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Trigger"));
	InteractableComponent->SetupAttachment(this);
	InteractableComponent->bRequireUseButton = false;
}


// Called when the game starts
void UDialogueTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bPlayOnTrigger)
		InteractableComponent->OnTriggerEnter.AddDynamic(this, &UDialogueTriggerComponent::OnTriggerEnter);
	else
		OnTriggerEnter();
}

void UDialogueTriggerComponent::OnTriggerEnter()
{
	ASpaceGameStateBase::Instance(GetWorld())->DialogueManager->PlayDialogue(DialogueName);

	this->DestroyComponent(true);
}
