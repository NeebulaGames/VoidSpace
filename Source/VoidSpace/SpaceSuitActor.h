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

	void Tick(float DeltaSeconds) override;

	void StartConsumingOxygen();
	void StopConsumingOxygen();

	UFUNCTION(BlueprintCallable, Category = SpacesuitOxygen)
	float GetRemainingOxygen() const;

	UFUNCTION(BlueprintCallable, Category = SpacesuitOxygen)
	bool IsConsumingOxygen() const;

	UPROPERTY(VisibleAnywhere, Category = Interactable)
	class UInteractableComponent* InteractableComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = SpacesuitOxygen)
	float OxygenDelta;

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

	UFUNCTION()
	void OnEventStarted();

	UFUNCTION()
	void OnEventFinished();

	bool bConsumingOxygen = false;

	bool bActive = false;

	class UGameEventManager* GameEventManager = nullptr;

	bool bCountingDown = false;

	float TimeRemaining = 0.f;

	float OxygenTime = 120.f;
};
