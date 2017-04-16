// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "SimonButtonActor.h"
#include "SimonStandActor.generated.h"

UCLASS()
class VOIDSPACE_API ASimonStandActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimonStandActor();

	virtual void Tick(float DeltaTime) override;

	void PostInitializeComponents() override;
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	TArray<ASimonButtonActor*> Buttons;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = SimonStand, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SimonStandMesh;

};
