// All rights Neebula Games

#pragma once

#include "Components/SceneComponent.h"
#include "DialogueTriggerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOIDSPACE_API UDialogueTriggerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueTriggerComponent();

	UPROPERTY(EditAnywhere, Category = Dialogue)
	FString DialogueName;

	UPROPERTY(EditAnywhere, Category = Dialogue)
	bool bPlayOnTrigger;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = Trigger, meta = ( AllowPrivateAccess = "true", EditCondition = "bPlayOnTrigger" ))
	class UInteractableComponent* InteractableComponent;

	UFUNCTION()
	void OnTriggerEnter();
	
};
