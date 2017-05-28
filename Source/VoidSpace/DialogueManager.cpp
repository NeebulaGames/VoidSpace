// All rights Neebula Games

#include "VoidSpace.h"
#include "DialogueManager.h"
#include "DialogueLookupTable.h"

UDialogueManager::UDialogueManager()
{
}

void UDialogueManager::LoadManager(const FString& name)
{
	ConstructorHelpers::FObjectFinder<UDataTable>
		DataTable(*name);

	DialogueLookupTable = DataTable.Object;
}

void UDialogueManager::PlayDialogue(const FString& name)
{
	static const FString ContextString(TEXT("GENERAL"));
	static FTimerHandle unusedHandle;
	static FTimerHandle unusedHandle2;

	FDialogueLookupTable* row = DialogueLookupTable->FindRow<FDialogueLookupTable>(*name, ContextString, true);

	if (row)
	{
		UGameplayStatics::PlayDialogue2D(GetWorld(), row->DialogueWave.Get(), DialogueContext);

		if (!row->NextDialogue.IsEmpty())
		{
			FTimerDelegate callback;
			callback.BindLambda([&row, this]() -> void {this->PlayDialogue(row->NextDialogue); });
			float delay = row->DialogueWave.Get()->GetWaveFromContext(DialogueContext)->GetDuration() + row->NextDialogueDelay;
			GetWorld()->GetTimerManager().SetTimer(unusedHandle, callback, delay, false);
		}

		if (row->Trigger)
		{
			FTimerDelegate callback;
			callback.BindLambda([name, this]() -> void {OnDialogueFinished.Broadcast(name); });
			float delay = row->DialogueWave.Get()->GetWaveFromContext(DialogueContext)->GetDuration();
			GetWorld()->GetTimerManager().SetTimer(unusedHandle2, callback, delay, false);
		}
	}
	else
	{
		UE_LOG(DialogueManager, Error, TEXT("Dialogue %s not found!"), *name);
	}
}
