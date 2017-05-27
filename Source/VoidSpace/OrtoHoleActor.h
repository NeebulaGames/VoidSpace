// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "OrtoHoleActor.generated.h"

UCLASS()
class VOIDSPACE_API AOrtoHoleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrtoHoleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void BeginClose();

	void StopClose();

private:

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* HoleMeshComponent = nullptr;


	
};
