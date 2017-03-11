// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "SpaceSuitActor.generated.h"

UCLASS()
class VOIDSPACE_API ASpaceSuitActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceSuitActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "Space Suit")
	class UStaticMeshComponent* SpaceSuitComponent;

	class UInteractableComponent* InteractableComponent;
};
