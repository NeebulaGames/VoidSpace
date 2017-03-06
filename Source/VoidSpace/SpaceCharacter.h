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

	UFUNCTION(Exec, Category = ExecFunctions)
	void KillPlayer(int mode) const;

private:
	void Use();

};
