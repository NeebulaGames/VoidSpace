// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OutsideLightActor.generated.h"

UCLASS()
class PROJECTMILA_API AOutsideLightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOutsideLightActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = OutsideLight, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;
	
	UMaterialInstanceDynamic* MaterialInstance;

	UPROPERTY(VisibleAnywhere, Category = GameEventManager)
	class UGameEventManager* GameEventManager;

	UPROPERTY(EditAnywhere, Category = OutsideLight, meta = (AllowPrivateAccess = "true"))
	bool bIsBreachSide;

	bool bBlinkLight = true;

	UFUNCTION()
	void OnBreathlessEvent();
};
