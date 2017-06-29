// All rights Neebula Games

#include "ProjectMILA.h"
#include "VoidSpacePlayerController.h"

void AVoidSpacePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}

