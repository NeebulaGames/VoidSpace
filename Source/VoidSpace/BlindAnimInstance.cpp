// All rights Neebula Games

#include "VoidSpace.h"
#include "BlindAnimInstance.h"
#include "SimonStandActor.h"


UBlindAnimInstance::UBlindAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bIsClosed(true)
{
}

void UBlindAnimInstance::OnSimonCompleted()
{
	bIsOpening = true;
}

void UBlindAnimInstance::SetSimonStandToInstance(ASimonStandActor* SimonStand)
{
	SimonStand->OnSimonCompleted.AddDynamic(this, &UBlindAnimInstance::OnSimonCompleted);
}

