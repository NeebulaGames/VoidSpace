// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HighlightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOIDSPACE_API UHighlightComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHighlightComponent();
	UHighlightComponent(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = HighlightConfig)
	bool bHighlight = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UMeshComponent* ParentMesh = nullptr;

public:

	virtual void OnBeginLooking();
	virtual void OnStopLooking();
	
};
