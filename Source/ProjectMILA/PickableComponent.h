// All rights Neebula Games

#pragma once

#include "HighlightComponent.h"
#include "PickableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMILA_API UPickableComponent : public UHighlightComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void PickedUp();

	UPROPERTY(EditAnywhere, Category=PickableConfig)
	bool bIgnorePlayerCollision = true;
};
