// All rights Neebula Games

#pragma once

#include "DialogueLookupTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct VOIDSPACE_API FDialogueLookupTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FDialogueLookupTable()
		: Trigger(false), NextDialogueDelay(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	FString DialogueName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	TAssetPtr<UDialogueWave> DialogueWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	bool Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	FString NextDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	int NextDialogueDelay;
};
