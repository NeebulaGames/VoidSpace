// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "EndGameTrigger.generated.h"

UCLASS()
class VOIDSPACE_API AEndGameTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndGameTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UFUNCTION()
	void OnTriggerEnter();

	UFUNCTION()
	void OnDialogueCompleted(const FString& finishedDialogue);

	UPROPERTY(VisibleAnywhere, Category = TriggerConfig)
	class UInteractableComponent* InteractableComponent;
	
	
};
