// All rights Neebula Games

#include "ProjectMILA.h"
#include "OrtoHoleAnimInstance.h"

UOrtoHoleAnimInstance::UOrtoHoleAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bIsClosing(false), bIsOpened(true), bIsClosed(false)
{
}
