// All rights Neebula Games

#pragma once

#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOIDSPACE_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerAction);

public:
	// Sets default values for this component's properties
	UInteractableComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Trigger() const;

public:
	UPROPERTY(BlueprintAssignable, Category = "Trigger")
		FOnTriggerAction OnTriggerAction;

	UPROPERTY(EditAnywhere, Category = "Trigger")
		uint32 TriggerDistance;

	UPROPERTY(VisibleAnywhere, Category = "Trigger debug")
		bool bPlayerIsNear;

};
