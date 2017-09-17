// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ProjectMILA.h"
#include "HighlightComponent.generated.h"

UENUM()
enum class EHighlightColor : uint32
{
	NONE = 0,
	Orange = 254,
	Blue = 255
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMILA_API UHighlightComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHighlightComponent();
	UHighlightComponent(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = HighlightConfig)
	bool bHighlight = true;

	UPROPERTY(EditAnywhere, Category = HighlightConfig)
	EHighlightColor HighlightColor = EHighlightColor::Orange;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UMeshComponent* ParentMesh = nullptr;

public:

	virtual void OnBeginLooking();
	virtual void OnStopLooking();
	
};
