// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "MessageTriggerActor.generated.h"

UCLASS()
class VOIDSPACE_API AMessageTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMessageTriggerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnTriggerEnter();

	UPROPERTY(VisibleAnywhere, Category = DisplayProperties)
	class UInteractableComponent* InteractableComponent;

public:

	UPROPERTY(EditAnywhere, Category = DisplayProperties)
	bool bOneShot;

	UPROPERTY(EditAnywhere, Category = DisplayProperties)
	float DisplayTime;

	UPROPERTY(EditAnywhere, Category = DisplayProperties)
	FColor DisplayColor;

	UPROPERTY(EditAnywhere, Category = DisplayProperties)
	FString DisplayText;
	
};
