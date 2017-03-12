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
	UPROPERTY(BlueprintAssignable, Category = TriggerConfig)
	FOnTriggerAction OnTriggerAction;

private:
	UPROPERTY(EditAnywhere, Category = TriggerConfig)
	bool bRequireUseButton;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, Category = "Trigger debug")
	bool bPlayerIsNear;

	UFUNCTION()
	void OnBeginOverlap(AActor* actor1, AActor* actor2);
	
	UFUNCTION()
	void OnEndOverlap(AActor* actor1, AActor* actor2);
};
