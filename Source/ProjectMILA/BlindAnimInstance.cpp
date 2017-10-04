// All rights Neebula Games

#include "ProjectMILA.h"
#include "GameEventManager.h"
#include "SpaceGameStateBase.h"
#include "BlindAnimInstance.h"

UBlindAnimInstance::UBlindAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bIsClosed(true)
{		
}


bool UBlindAnimInstance::IsBeginningEvent()
{
	UGameEventManager* manager = ASpaceGameStateBase::Instance(this)->GameEventManager;
	if (manager->GetCurrentEvent()->Name == "Beginning")
		return true;
	return false;
}