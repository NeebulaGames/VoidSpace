// All rights Neebula Games

#pragma once

#include "GameFramework/PlayerController.h"
#include "VoidSpacePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSPACE_API AVoidSpacePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;	
	
};
