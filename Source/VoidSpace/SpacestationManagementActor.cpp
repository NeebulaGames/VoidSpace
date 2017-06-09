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

}

void ASpacestationManagementActor::OnEventStarted()
{
	UGameEventManager::FEvent* current = EventManager->GetCurrentEvent();

	LightsState = current->LightsState;
	LedsState = current->LedsState;
}
