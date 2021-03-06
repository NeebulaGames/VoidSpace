// All rights Neebula Games

#include "ProjectMILA.h"
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
	if (bReduceLifeTime)
	{
		LifeTime -= DeltaSeconds;
		LifeTime = FMath::Max(LifeTime, 0.f);
	}

	UGameEventManager::FEvent* current = EventManager->GetCurrentEvent();

	if (EventManager->IsCounting())
	{
		float time = bReduceLifeTime ? LifeTime : EventManager->GetTime();
		if (current->DeathReason == EDeathReason::Choke)
		{
			ScreensState = EScreenState::SCREEN_WARNING_OXYGEN;
			ScreenMessage = FString::Printf(TEXT("%02d%%"), FMath::FloorToInt(time * ReduceFactor));
		}
		else
		{
			ScreensState = EScreenState::SCREEN_WARNING_METEORITE;
			ScreenMessage = FString::Printf(TEXT("%02d:%02d"), FMath::FloorToInt(time / 60.f), FMath::FloorToInt(FMath::Fmod(time, 60.f)));
		}
	}
	else
	{
		if (current && current->DeathReason == EDeathReason::Meteor)
			ScreensState = EScreenState::SCREEN_NOSIGNAL;
		else
			ScreensState = EScreenState::SCREEN_OK;
		ScreenMessage.Reset(0);
	}
}

void ASpacestationManagementActor::OnEventStarted()
{
	UGameEventManager::FEvent* current = EventManager->GetCurrentEvent();

	LightsState = current->LightsState;
	LedsState = current->LedsState;
	
	if (current->DeathReason == EDeathReason::Meteor)
	{
		ReduceFactor = 100.f / current->Time;
	}
}
