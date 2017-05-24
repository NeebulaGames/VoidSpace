// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "VitrineActor.generated.h"

UCLASS()
class VOIDSPACE_API AVitrineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVitrineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void NotifyActorBeginOverlap(AActor* OtherActor);

private:	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* VitrineMeshComponent;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInteractableComponent* InteractableComponent;

	UPROPERTY(EditAnywhere, Category = SpaceSuitInside, meta = (AllowPrivateAccess = "true"))
	class ASpaceSuitActor* SpaceSuitActor;
	
};
