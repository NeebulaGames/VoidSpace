// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InformativeScreen.generated.h"

UCLASS()
class PROJECTMILA_API AInformativeScreen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInformativeScreen();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* ScreenMesh;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* Text;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	class ASpacestationManagementActor* StationManager;

	void SetScreenMat(UMaterial* mat);

	void SetTextToScren(FText string);

	UMaterial* MaterialNoSignal;
	UMaterial* MaterialStatusOK;
	UMaterial* MaterialWarningMeteorStorm;
	UMaterial* MaterialWarningOxygen;
	
};
