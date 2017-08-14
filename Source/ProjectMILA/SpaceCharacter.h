// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SpaceCharacter.generated.h"

enum class EDeathReason : uint8;
class ASpaceSuitActor;

UCLASS()
class PROJECTMILA_API ASpaceCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpaceCharacter();

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void ReleaseObject();
	void ToggleGravity();
	void ToggleSpaceSuit(ASpaceSuitActor* spaceSuit);

	UFUNCTION(BlueprintCallable, Category = Spacesuit)
	bool WearsSpaceSuit() const;

	UFUNCTION(BlueprintCallable, Category = Spacesuit)
	ASpaceSuitActor* GetEquippedSuit() const;
	
	UFUNCTION(Exec, Category = ExecFunctions)
	float KillPlayer(EDeathReason mode);

	UPhysicsHandleComponent* physics_handle;
	AActor* pickedObject = nullptr;

	class UEquipableComponent* EquippedObject = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "PlayerCamera")
	class UCameraComponent* FirstPersonCameraComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraBobbing)
	TSubclassOf<UCameraShake> CameraBobbing;

protected:

	FVector offset = FVector(0.f, 0.f, 50.f);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//handles moving forward/backward
	UFUNCTION()
	void MoveForward(float Val);
	//handles strafing
	UFUNCTION()
	void MoveHorizontal(float Val);

	UFUNCTION()
	void MoveVertical(float Val);

	UFUNCTION()
	void OnStartJump();

	UFUNCTION()
	void OnStopJump();

	UFUNCTION()
	void OnStartSprint();
	
	UFUNCTION()
	void OnStopSprint();

	UFUNCTION()
	void OnFire();

	UFUNCTION()
	void OnEndFire();

private:
	void Use();

	void SprintControl(float DeltaTime);

	bool CastRay(FHitResult& result);

	bool bIsSprinting = false;
	bool bIsRecovering = false;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float WalkSpeed = 600;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float RunSpeed = 1000;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float EVASpeed = 200;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float StaminaDuration = 100;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float StaminaRecovery = 0.3f;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float StaminaConsumition = 0.6f;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float MaxStamina = 100;

	UPROPERTY(EditAnywhere, Category = CameraBobbing)
	float RunScale = 2;

	UPROPERTY(EditAnywhere, Category = CameraBobbing)
	float WalkScale = 1;

	class UHighlightComponent* LookedObject = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Spacesuit, meta = (AllowPrivateAccess = "true"))
	ASpaceSuitActor* EquippedSuit = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SpaceSuit, meta = (AllowPrivateAccess = "true"))
	bool bGravityEnabled = true;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* LeftJetpackSmokeComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* RightJetpackSmokeComponent = nullptr;

	float ForwardAxisVal;

	UPROPERTY(EditAnywhere, Category = Audio)
	class UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere, Category = DeathCinematics)
	class ULevelSequence* ChokeDeathSequence = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Audio)
	class USoundWave* EVASound;

	UPROPERTY(VisibleAnywhere, Category = Audio)
	class USoundCue* FootstepsCue;

	APlayerController* playerController;

};
