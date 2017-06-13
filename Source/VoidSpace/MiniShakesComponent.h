// All rights Neebula Games

#pragma once

#include "Components/ActorComponent.h"
#include "MiniShakesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOIDSPACE_API UMiniShakesComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMiniShakesComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	TSubclassOf<UCameraShake> CameraMiniShakes;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	UFUNCTION()
	void OnOverlap(AActor* actor1, AActor* actor2);

	UFUNCTION()
	void TriggerMiniShake();

	UFUNCTION()
	void TriggerMiniShakeWithDelay(float seconds);

	UFUNCTION()
	void StopMiniShakes();
	
	UFUNCTION()
	void StartMiniShakes();

	FTimerHandle MiniShakeTimerHandle;

	APlayerController* playerController;

	bool bIsPlayingMiniShakes;

	const float MIN_SHAKE_DELAY = 1.f;
	const float MAX_SHAKE_DELAY = 2.f;
	const float MIN_SHAKE_SCALE = 0.f;
	const float MAX_SHAKE_SCALE = 1.f;
};
