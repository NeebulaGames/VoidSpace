// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "InteractableComponent.h"
#include "SpaceSuitActor.generated.h"

UCLASS()
class VOIDSPACE_API ASpaceSuitActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceSuitActor(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, Category = Interactable)
	class UInteractableComponent* InteractableComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = SpaceSuit)
	USoundWave* Zipper;

	UPROPERTY(VisibleAnywhere, Category = SpaceSuit, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SpaceSuitComponent;

	UFUNCTION()
	void OnSuitTrigger();

	UFUNCTION()
	void OnFadeOutFinish();

	UFUNCTION()
	void OnSoundFinished();

	UFUNCTION()
	void OnFadeInFinished();
};
