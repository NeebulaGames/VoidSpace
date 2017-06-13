// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InformativeScreen.generated.h"

UCLASS()
class VOIDSPACE_API AInformativeScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInformativeScreen();

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* ScreenMesh;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* Text;

private:

	class ASpacestationManagementActor* StationManager;

	void SetScreenMat(UMaterial* mat);

	void SetTextToScren(FText string);

	UMaterial* MaterialNoSignal;
	UMaterial* MaterialStatusOK;
	UMaterial* MaterialWarningMeteorStorm;
	UMaterial* MaterialWarningOxygen;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
