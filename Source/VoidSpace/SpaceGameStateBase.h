// All rights Neebula Games

#pragma once

#include "GameFramework/GameStateBase.h"
#include "SpaceGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class VOIDSPACE_API ASpaceGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Exec, Category = ExecFunctions)
	void TogglePlayerGravity() const;	

	UFUNCTION(Exec, Category = ExecFunctions)
	void ToggleSpaceSuit(bool activate) const;

	static ASpaceGameStateBase* Instance(UObject* world);

	UPROPERTY(VisibleAnywhere)
	bool bMovementAllowed = true;
	
	UPROPERTY(VisibleAnywhere)
	bool bInteractionAllowed = true;
};
