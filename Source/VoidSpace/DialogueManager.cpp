// All rights Neebula Games

#include "VoidSpace.h"
#include "DialogueManager.h"
#include "DialogueLookupTable.h"

UDialogueManager::UDialogueManager()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));

	AudioComponent->bIsUISound = true;
}

void UDialogueManager::LoadManager(const FString& name)
{
	ConstructorHelpers::FObjectFinder<UDataTable>
		DataTable(*name);

	LoadManager(DataTable.Object);
}

void UDialogueManager::LoadManager(UDataTable* dataTable)
{
	DialogueLookupTable = dataTable;
}

void UDialogueManager::PlayDialogue(const FString& name)
{
	static const FString ContextString(TEXT("GENERAL"));
	static FTimerHandle unusedHandle;
	static FTimerHandle unusedHandle2;

	FDialogueLookupTable* row = DialogueLookupTable->FindRow<FDialogueLookupTable>(*name, ContextString, true);

	if (row)
	{
		UWorld* World = GetOuter()->GetWorld();

		USoundCue* wave = row->DialogueWave.LoadSynchronous();
		AudioComponent->SetSound(wave);
		AudioComponent->Play(0.f);
		//UGameplayStatics::PlaySound2D(World, wave);

		if (!row->NextDialogue.IsEmpty())
		{
			FTimerDelegate callback;
			callback.BindLambda([&row, this]() -> void {this->PlayDialogue(row->NextDialogue); });
			float delay = wave->GetDuration() + row->NextDialogueDelay;
			World->GetTimerManager().SetTimer(unusedHandle, callback, delay, false);
		}

		if (row->Trigger)
		{
			FTimerDelegate callback;
			callback.BindLambda([name, this]() -> void {OnDialogueFinished.Broadcast(name); });
			float delay = wave->GetDuration();
			World->GetTimerManager().SetTimer(unusedHandle2, callback, delay, false);
		}
	}
	else
	{
		UE_LOG(DialogueManager, Error, TEXT("Dialogue %s not found!"), *name);
	}
}
