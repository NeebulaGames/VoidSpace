// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "EscapePodActor.generated.h"

UCLASS()
class PROJECTMILA_API AEscapePodActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEscapePodActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = ElevatorInteractable)
	AActor* TeleportPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = EndingCinematics)
	class ULevelSequence* EndSequence = nullptr;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* EscapePodMeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponentToOpenPod;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponentToClosePod;

	UPROPERTY(VisibleAnywhere)
	class UEscapePodAnimInstance* EscapePodAnimInstance;

	UFUNCTION()
	void OnControlRoomEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEscapePodEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFadeOutFinish();

	bool bWasClosing = false;

	UPROPERTY(EditAnywhere, Interp)
	bool bClose = false;

	UCameraComponent* PlayerCamera = nullptr;

	FVector CameraOriginalPosition;
	FRotator CameraOriginalRotation;

	float Movement = 0.f;
};
