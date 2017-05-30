// All rights Neebula Games

#pragma once

#include "Components/SceneComponent.h"
#include "InteractableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), HideCategories = (Transform,Mobility) )
class VOIDSPACE_API UInteractableComponent : public USceneComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerAction);

public:
	// Sets default values for this component's properties
	UInteractableComponent(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts
	virtual void BeginPlay() override;

	void Trigger() const;

public:
	// Triggers when the action button is pressed
	UPROPERTY(BlueprintAssignable, Category = TriggerConfig)
	FOnTriggerAction OnTriggerAction;

	// Triggers when a character enters in the trigger cube
	UPROPERTY(BlueprintAssignable, Category = TriggerConfig)
	FOnTriggerAction OnTriggerEnter;

	// Triggers when a character exits the trigger cube
	UPROPERTY(BlueprintAssignable, Category = TriggerConfig)
		FOnTriggerAction OnTriggerExit;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = TriggerConfig)
	bool bRequirePlayerNear;

	UPROPERTY(EditAnywhere, Category = TriggerConfig)
	bool bRequireUseButton;

private:

	UPROPERTY(VisibleAnywhere, Category = "Trigger debug")
	bool bPlayerIsNear;

	UFUNCTION()
	void OnBeginOverlap(AActor* actor1, AActor* actor2);
	
	UFUNCTION()
	void OnEndOverlap(AActor* actor1, AActor* actor2);
};
