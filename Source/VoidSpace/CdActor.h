// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "CdActor.generated.h"

UCLASS()
class VOIDSPACE_API ACdActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACdActor();

private:
	UPROPERTY(VisibleAnywhere, Category = SpaceSuit, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Interactable, meta = (AllowPrivateAccess = "true"))
	class UPickableComponent* PickableComponent;
};
