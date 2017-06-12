// All rights Neebula Games

#include "VoidSpace.h"
#include "SpacestationManagementActor.h"
#include "SpaceGameStateBase.h"
#include "GameEventManager.h"


// Sets default values
ASpacestationManagementActor::ASpacestationManagementActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpacestationManagementActor::BeginPlay()
{
	Super::BeginPlay();
	
	EventManager = ASpaceGameStateBase::Instance(GetWorld())->GameEventManager;

	EventManager->OnEventStarted.AddDynamic(this, &ASpacestationManagementActor::OnEventStarted);
}

void ASpacestationManagementActor::Tick(float DeltaSeconds)
{
	if (bReduceOxygen)
		OxygenTime -= DeltaSeconds;

	UGameEventManager::FEvent* current = EventManager->GetCurrentEvent();

	if (EventManager->IsCounting())
	{
		float time = EventManager->GetTime();
		if (current->DeathReason == 2)
		{
			ScreensState = EScreenState::SCREEN_WARNING_OXYGEN;
			ScreenMessage = FString::Printf(TEXT("%02d%%"), FMath::Floor((bReduceOxygen ? OxygenTime : time) * ReduceFactor));
		}
		else
		{
			ScreensState = EScreenState::SCREEN_WARNING_METEORITE;
			ScreenMessage = FString::Printf(TEXT("%02d:%02d"), FMath::Floor(time / 60.f), FMath::Floor(FMath::Fmod(time, 60.f)));
		}
	}
	else
	{
		if (current->DeathReason == 0)
			ScreensState = EScreenState::SCREEN_OK;
		else if (current->DeathReason == 1)
			ScreensState = EScreenState::SCREEN_NOSIGNAL;
		ScreenMessage.Reset(0);
	}
}

void ASpacestationManagementActor::OnEventStarted()
{
	UGameEventManager::FEvent* current = EventManager->GetCurrentEvent();

	LightsState = current->LightsState;
	LedsState = current->LedsState;
	
	if (current->DeathReason == 1)
	{
		ReduceFactor = 100.f / current->Time;
	}
}
