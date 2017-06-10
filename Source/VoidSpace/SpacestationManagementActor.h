// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceStatics.h"
#include "SpacestationManagementActor.generated.h"

UENUM(BlueprintType)
enum class EScreenState : uint8
{
	SCREEN_NOSIGNAL,
	SCREEN_OK,
	SCREEN_WARNING
};

UCLASS()
class VOIDSPACE_API ASpacestationManagementActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ASpacestationManagementActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SpacestationState)
	FString ScreenMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SpacestationState)
	EScreenState ScreensState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SpacestationState)
	ELightState LightsState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SpacestationState)
	ELedState LedsState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SpacestationControl)
	float OxygenTime = 0.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SpacestationControl)
	bool bReduceOxygen = false;

private:

	void OnEventStarted();

	class UGameEventManager* EventManager;
	float ReduceFactor = 0.f;
};
