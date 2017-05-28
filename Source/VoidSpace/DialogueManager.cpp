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

	FDialogueLookupTable* row = DialogueLookupTable->FindRow<FDialogueLookupTable>(*name, ContextString, true);

	if (row)
	{
		UGameplayStatics::PlayDialogue2D(GetWorld(), row->DialogueWave.Get(), DialogueContext);
	}
	else
	{
		UE_LOG(DialogueManager, Error, TEXT("Dialogue %s not found!"), *name);
	}
}
