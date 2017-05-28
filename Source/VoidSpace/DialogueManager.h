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

	UFUNCTION(BlueprintCallable, Category = DialogueManager)
	void LoadManager(UDataTable* dataTable);

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	void PlayDialogue(const FString& name);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DialogueProperties)
	FDialogueContext DialogueContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DialogueProperties)
	UDataTable* DialogueLookupTable;
	
	UPROPERTY(BlueprintAssignable, Category = DialogueEvents)
	FOnDialogueFinished OnDialogueFinished;
};
