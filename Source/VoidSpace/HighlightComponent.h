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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnBeginLooking();
	virtual void OnStopLooking();

private:

	UStaticMeshComponent* ParentMesh = nullptr;
};
