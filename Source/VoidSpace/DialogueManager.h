// All rights Neebula Games

#pragma once

#include "UObject/NoExportTypes.h"
#include "DialogueManager.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSPACE_API UDialogueManager : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueFinished, const FString&, finishedDialogue);
	
public:

	UDialogueManager();

	void LoadManager(const FString& file);

	void PlayDialogue(const FString& name);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	FDialogueContext DialogueContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	UDataTable* DialogueLookupTable;
	
	UPROPERTY(BlueprintAssignable, Category = Dialogue)
	FOnDialogueFinished OnDialogueFinished;
};
