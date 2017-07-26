// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "ExitVault.generated.h"

UCLASS()
class PROJECTMILA_API AExitVault : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExitVault();

	UFUNCTION()
	void OpenInnerDoor() const;

	UFUNCTION()
	void OpenExternalDoor() const;

	UFUNCTION()
	void CloseInnerDoor() const;

	UFUNCTION()
	void CloseExternalDoor() const;

	UPROPERTY(EditAnywhere, Category = SmokeSound)
	USoundWave* Smoke;

	UPROPERTY(EditAnywhere)
	bool bExternalDoorOpen = false;

	UPROPERTY(EditAnywhere, Category = Lever, meta = (AllowPrivateAccess = "true"))
	class AExitVaultLever* Lever;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* DepressuringSystem01;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* DepressuringSystem02;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* DepressuringSystem03;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* DepressuringSystem04;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* BottomSmokeSystem;

	UPROPERTY(VisibleAnywhere, Category = DoorMesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ExitInnerDoorMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = DoorMesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ExitExternalDoorMeshComponent;

	UFUNCTION()
	void OnLeverUse();

private:
	void doDepressurising() const;

	void ToogleGravity() const;

	void ChangeDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
};
