// All rights Neebula Games

#include "VoidSpace.h"
#include "ExitVaultDoorAnimInstance.h"


UExitVaultDoorAnimInstance::UExitVaultDoorAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bIsOpening(false), bIsClosing(false), bIsOpened(false), bIsClosed(false)
{
}

