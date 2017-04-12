// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SpaceCharacter.generated.h"

UCLASS()
class VOIDSPACE_API ASpaceCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpaceCharacter();

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void ToggleGravity();
	void ToggleSpaceSuit(bool activate);

	UPhysicsHandleComponent* physics_handle;

	UFUNCTION(Exec, Category = ExecFunctions)
	void KillPlayer(int mode) const;

protected:

	AActor* pickedObject = nullptr;
	FHitResult LastHitted;
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
		void OnStartJump();

	UFUNCTION()
		void OnStopJump();

	UFUNCTION()
		void OnStartSprint();
	
	UFUNCTION()
		void OnStopSprint();

private:
	void Use();

	void SprintControl(float DeltaTime);

	bool bIsSprinting = false;
	bool bIsRecovering = false;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float WalkSpeed = 600;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float RunSpeed = 1000;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float StaminaDuration = 100;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float StaminaRecovery = 0.3f;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float StaminaConsumition = 0.6f;

	UPROPERTY(EditAnywhere, Category = "WalkAndRun")
	float MaxStamina = 100;


	bool bGravityEnabled = true;
	bool bWearsSpaceSuit = false;
};
