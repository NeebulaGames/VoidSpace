// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorPanel.generated.h"


UCLASS()
class VOIDSPACE_API ADoorPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorPanel();
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PanelMesh;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* ScreenText;

protected:

	void BeginPlay() override;
	void OnConstruction(const FTransform& Transform) override;

private:
	UMaterialInstanceDynamic* ScreenMaterial = nullptr;
	
};
