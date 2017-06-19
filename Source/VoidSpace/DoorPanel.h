// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorPanel.generated.h"

UENUM(BlueprintType)
enum class PanelModule : uint8
{
	PANEL_BEDROOM,
	PANEL_EXITVAULT,
	PANEL_MAINTENANCE,
	PANEL_OBSERVATORY,
	PANEL_CONTROLROOM
};

UCLASS()
class VOIDSPACE_API ADoorPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorPanel();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PanelMesh;

	UPROPERTY(EditAnywhere)
	PanelModule PanelModuleText;

protected:
	virtual void BeginPlay() override;

private:
	UMaterial* MaterialBedroom;
	UMaterial* MaterialExitVault;
	UMaterial* MaterialMaintenance;
	UMaterial* MaterialObservatory;
	UMaterial* MaterialControlRoom;
	
};
