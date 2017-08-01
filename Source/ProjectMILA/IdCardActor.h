// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "IdCardActor.generated.h"

UCLASS()
class PROJECTMILA_API AIdCardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIdCardActor();

private:	
	UPROPERTY(VisibleAnywhere, Category = SpaceSuit, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Interactable, meta = (AllowPrivateAccess = "true"))
	class UPickableComponent* PickableComponent;

	
	
};
