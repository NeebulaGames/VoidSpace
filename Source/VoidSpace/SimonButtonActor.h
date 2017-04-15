// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "SimonButtonActor.generated.h"

UCLASS()
class VOIDSPACE_API ASimonButtonActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimonButtonActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = SimonButton, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SimonButtonMesh;
	

	UMaterialInstanceDynamic* ButtonMaterial = nullptr;
};
