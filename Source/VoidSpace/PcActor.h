// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "PcActor.generated.h"

UCLASS()
class VOIDSPACE_API APcActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APcActor(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = PcMesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* PcMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Interactable, meta = (AllowPrivateAccess = "true"))
	class UInteractableComponent* InteractableComponent;

	UFUNCTION()
	void OnEnterCd();
	void OnActivePc();
};
