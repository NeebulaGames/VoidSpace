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

protected:

public:

	ASpaceGameStateBase();

	UFUNCTION(BlueprintCallable, Category = GameEventManager)
	void StartEventSM();

	UFUNCTION(Exec, Category = ExecFunctions)
	void TogglePlayerGravity() const;	

	UFUNCTION(Exec, Category = ExecFunctions)
	void ToggleSpaceSuit(bool activate) const;

	void Die(int reason);

	// TODO: Remove me! Only for testing purposes
	UFUNCTION(Exec)
	void FinishEvent();

	static ASpaceGameStateBase* Instance(UObject* world);

	UPROPERTY(VisibleAnywhere)
	bool bMovementAllowed = true;
	
	UPROPERTY(VisibleAnywhere)
	bool bInteractionAllowed = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameEventManager)
	bool bLoadEventSM = true;

	UPROPERTY(VisibleAnywhere, Category = GameEventManager)
	class UGameEventManager* GameEventManager;
};
