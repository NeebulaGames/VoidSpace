// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "VitrineActor.generated.h"

UCLASS()
class PROJECTMILA_API AVitrineActor : public AActor
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
	UPROPERTY(VisibleAnywhere, Category = Audio)
	USoundWave* OpenVitrineSound;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* VitrineMeshComponent;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = SpaceSuitInside, meta = (AllowPrivateAccess = "true"))
	class ASpaceSuitActor* SpaceSuitActor;
	
};
