// All rights Neebula Games

#pragma once

#include "Components/ActorComponent.h"
#include "GravityTogglerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMILA_API UGravityTogglerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGravityTogglerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlap(AActor* actor1, AActor* actor2);
};
