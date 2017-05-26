// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "ExitVault.generated.h"

UCLASS()
class VOIDSPACE_API AExitVault : public AActor
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

private:
	bool isOutside = false;

	void doDepressurising() const;

	void ToogleGravity() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = SmokeSound)
	USoundWave* Smoke;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleSystem;

	UPROPERTY(VisibleAnywhere, Category = DoorMesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ExitInnerDoorMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = DoorMesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* ExitExternalDoorMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Interactable, meta = (AllowPrivateAccess = "true"))
	class UInteractableComponent* InteractableComponent;
	
	UFUNCTION()
	void OnVaultEnter();

	UFUNCTION()
	void OnVaultExit();
};
