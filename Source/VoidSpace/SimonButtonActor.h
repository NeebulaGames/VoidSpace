// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "SimonButtonActor.generated.h"

UCLASS()
class VOIDSPACE_API ASimonButtonActor : public AActor
{
	GENERATED_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FSimonButtonClicked, int);
	
public:	
	// Sets default values for this actor's properties
	ASimonButtonActor();

	virtual void Tick(float DeltaTime) override;

	void SetColor(const FLinearColor& color, float blink = 1.0f) const;
	void TurnOn();
	void TurnOff();

	UPROPERTY(VisibleAnywhere, Category = SimonButton)
	class UStaticMeshComponent* SimonButtonMesh;

	UPROPERTY(VisibleAnywhere, Category = Interactable)
	class UInteractableComponent* InteractableComponent;

	FSimonButtonClicked OnButtonClicked;

	UPROPERTY(VisibleAnywhere, Category = SimonButton)
	int ButtonNumber = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void ButtonClicked();

	float CountDown = -1.f;

	UMaterialInstanceDynamic* ButtonMaterial = nullptr;
};
