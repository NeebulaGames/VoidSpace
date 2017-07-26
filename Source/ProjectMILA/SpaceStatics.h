// All rights Neebula Games

#pragma once

UENUM(BlueprintType)
enum class EDeathReason : uint8
{
	None,
	Meteor,
	Choke,
	ChokeSpacesuit,
	Unknown
};

UENUM(BlueprintType)
enum class ELightState : uint8
{
	LIGHT_ON,
	LIGHT_OFF,
	LIGHT_EMERGENCY
};

UENUM(BlueprintType)
enum class ELedState : uint8
{
	LED_ON,
	LED_EMERGENCY
};


/**
 * 
 */
class PROJECTMILA_API USpaceStatics
{
public:

	static FORCEINLINE bool Trace(
		UWorld* World,
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		ECollisionChannel CollisionChannel = ECC_Visibility,
		bool ReturnPhysMat = true
	)
	{
		if (!World)
		{
			return false;
		}

		FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true, ActorToIgnore);
		TraceParams.bTraceComplex = true;
		//TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

		//Ignore Actors
		TraceParams.AddIgnoredActor(ActorToIgnore);

		//Re-initialize hit info
		HitOut = FHitResult(ForceInit);

		//Trace!
		World->LineTraceSingleByChannel(
			HitOut,		//result
			Start,	//start
			End, //end
			CollisionChannel, //collision channel
			TraceParams
		);

		//Hit any Actor?
		return (HitOut.GetActor() != nullptr);
	}
};
