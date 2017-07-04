// All rights Neebula Games

#include "ProjectMILA.h"
#include "OrtoHoleAnimInstance.h"

UOrtoHoleAnimInstance::UOrtoHoleAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bIsOpened(true), bIsClosed(false), bIsClosing(false)
{
}
