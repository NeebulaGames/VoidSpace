// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "ExitVaultLever.generated.h"

UCLASS()
class PROJECTMILA_API AExitVaultLever : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExitVaultLever();

	UPROPERTY(VisibleAnywhere, Category = Interactable, meta = (AllowPrivateAccess = "true"))
	class UInteractableComponent* InteractableComponent;

	UPROPERTY(EditAnywhere)
	bool bCanBTriggered = true;

	UFUNCTION()
	bool IsTriggering();

	UFUNCTION()
	bool IsNotTriggered();

	UFUNCTION()
	void SetbIsTriggering(bool value);

	UFUNCTION()
	void SetbIsNotTriggered(bool value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	UPROPERTY(VisibleAnywhere, Category = Interactable, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* LeverMeshComponent;	
};
