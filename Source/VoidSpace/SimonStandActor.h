// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "SimonButtonActor.h"
#include "SimonStandActor.generated.h"

UCLASS()
class VOIDSPACE_API ASimonStandActor : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimonCompleted);

public:
	// Sets default values for this actor's properties
	ASimonStandActor();

	virtual void Tick(float DeltaTime) override;

	void PostInitializeComponents() override;
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	TArray<ASimonButtonActor*> Buttons;

	UPROPERTY(BlueprintAssignable)
	FSimonCompleted OnSimonCompleted;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void RestoreButtons();
	void ContinueSequence();
	void ShutAllButtons();
	void GenerateSequence(int elements);
	void SequenceSuccess();
	void SequenceWrong();

	UFUNCTION()
	void EventStarted();

	UFUNCTION()
	void EventFinished();

	UFUNCTION()
	void ButtonPressed(int button);

	UPROPERTY(VisibleAnywhere, Category = SimonStand, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SimonStandMesh;

	UPROPERTY(VisibleAnywhere, Category = SimonStand, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SimonBoxCollider;

	bool bSimonCompleted = false;
	int SequencesSuccess = 0;
	int CurrentButtonSequence = 0;
	int CurrentSequencePosition = 0;
	static const FLinearColor Colors[3];
	bool bActivateSimon = false;
	TArray<int> Sequence;
	FTimerHandle TimerHandle;
};
