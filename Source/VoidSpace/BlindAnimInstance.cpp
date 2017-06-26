// All rights Neebula Games

#include "VoidSpace.h"
#include "BlindAnimInstance.h"
#include "SimonStandActor.h"
#include "SpaceGameStateBase.h"
#include "GameEventManager.h"


bool UBlindAnimInstance::bExecuted = false;


UBlindAnimInstance::UBlindAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bIsClosed(true)
{
}

void UBlindAnimInstance::SetExecuted(bool executed) const
{
	bExecuted = executed;
}

bool UBlindAnimInstance::HasExecuted() const
{
	return bExecuted;
}

void UBlindAnimInstance::FinishCurrentEvent()
{
	UGameEventManager* manager = ASpaceGameStateBase::Instance(this)->GameEventManager;
	if (manager->GetCurrentEvent()->Name == "Beginning")
		manager->FinishCurrentEvent();
}

bool UBlindAnimInstance::IsBeginningEvent()
{
	UGameEventManager* manager = ASpaceGameStateBase::Instance(this)->GameEventManager;
	if (manager->GetCurrentEvent()->Name == "Beginning")
		return true;
	return false;
}

void UBlindAnimInstance::OnSimonCompleted()
{
	bIsOpening = true;
	if(!bExecuted)
		UGameplayStatics::PlaySound2D(GetWorld(), BlindSound);
}

void UBlindAnimInstance::SetSimonStandToInstance(ASimonStandActor* SimonStand)
{
	SimonStand->OnSimonCompleted.AddDynamic(this, &UBlindAnimInstance::OnSimonCompleted);
}

