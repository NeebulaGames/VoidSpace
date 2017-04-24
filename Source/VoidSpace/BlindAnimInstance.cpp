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
	ASpaceGameStateBase::Instance(this)->GameEventManager->FinishCurrentEvent();
}

void UBlindAnimInstance::OnSimonCompleted()
{
	bIsOpening = true;
}

void UBlindAnimInstance::SetSimonStandToInstance(ASimonStandActor* SimonStand)
{
	SimonStand->OnSimonCompleted.AddDynamic(this, &UBlindAnimInstance::OnSimonCompleted);
}

