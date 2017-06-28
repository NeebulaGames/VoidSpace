// All rights Neebula Games

#include "VoidSpace.h"
#include "OrtoHoleAnimInstance.h"

UOrtoHoleAnimInstance::UOrtoHoleAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bIsOpened(true), bIsClosed(false), bIsClosing(false)
{
}
