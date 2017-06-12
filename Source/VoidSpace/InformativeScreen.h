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

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* Text;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	class ASpacestationManagementActor* StationManager;

	void SetScreenMat(UMaterial* mat);

	void SetTextToScren(FText string);

	UMaterial* MatNoSignal;
	UMaterial* MatStatusOk;
	UMaterial* MatWarningMeteo;
	UMaterial* MatWarningOX;
	
};
