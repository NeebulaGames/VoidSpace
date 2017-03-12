// All rights Neebula Games

#include "VoidSpace.h"
#include "VoidSpacePlayerController.h"

void AVoidSpacePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}

