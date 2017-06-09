// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceStatics.h"
#include "SpacestationManagementActor.generated.h"

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

	FString ScreenMessage;
	ELightState LightsState;
	ELedState LedsState;

private:

	void OnEventStarted();

	class UGameEventManager* EventManager;
};
