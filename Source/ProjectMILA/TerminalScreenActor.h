// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerminalScreenActor.generated.h"

UCLASS()
class PROJECTMILA_API ATerminalScreenActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerminalScreenActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldTickIfViewportsOnly() const override;

private:

	void BreakText(FString& text);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DisplayComponent;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* TextComponent;

	UPROPERTY(Interp, EditAnywhere, Category = ScreenText)
	int MaxLineWidth = 30;

	UPROPERTY(Interp, EditAnywhere, Category = ScreenText)
	float BlinkRatio = 0.5f;

	UPROPERTY(Interp, EditAnywhere, Category = ScreenText)
	FString Text;

	bool DisplaySlash = true;
	float NextBlinkTime = BlinkRatio;
};
