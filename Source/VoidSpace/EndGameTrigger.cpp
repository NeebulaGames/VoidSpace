// All rights Neebula Games

#include "VoidSpace.h"
#include "EndGameTrigger.h"
#include "InteractableComponent.h"
#include "SpaceGameStateBase.h"
#include "GameEventManager.h"
#include "DialogueManager.h"

// Sets default values
AEndGameTrigger::AEndGameTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
	RootComponent = InteractableComponent;
}

// Called when the game starts or when spawned
void AEndGameTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	InteractableComponent->OnTriggerEnter.AddDynamic(this, &AEndGameTrigger::OnTriggerEnter);
}

void AEndGameTrigger::OnTriggerEnter()
{
	UDialogueManager* dialogueManager = ASpaceGameStateBase::Instance(GetWorld())->DialogueManager;
	dialogueManager->PlayDialogue("Assistant_020");
	dialogueManager->OnDialogueFinished.AddDynamic(this, &AEndGameTrigger::OnDialogueCompleted);


	float delay = 1.f;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0.f, 1.f, delay, FLinearColor::Black, false, true);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, "Congratulations for completing the game");
}

void AEndGameTrigger::OnDialogueCompleted(const FString& finishedDialogue)
{
	ASpaceGameStateBase::Instance(this)->GameEventManager->FinishCurrentEvent();
}
