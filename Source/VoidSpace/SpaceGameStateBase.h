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


	void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, Category = GameEventManager)
	void StartEventSM();

	UFUNCTION(Exec, Category = ExecFunctions)
	void TogglePlayerGravity() const;	

	UFUNCTION(Exec, Category = ExecFunctions)
	void ToggleSpaceSuit(bool activate) const;

	UFUNCTION(Exec)
	void Die(int reason);

	void EndGame();

	// TODO: Remove me! Only for testing purposes
	UFUNCTION(Exec, BlueprintCallable)
	void FinishEvent();

	UFUNCTION(BlueprintCallable, Category = GameState)
	static ASpaceGameStateBase* Instance(UObject* world);

	UPROPERTY(VisibleAnywhere)
	bool bMovementAllowed = true;
	
	UPROPERTY(VisibleAnywhere)
	bool bInteractionAllowed = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameEventManager)
	bool bLoadEventSM = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameEventManager)
	class UGameEventManager* GameEventManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DialogueManager)
	class UDialogueManager* DialogueManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SpacestationManagement)
	class ASpacestationManagementActor* SpacestationManager;

};
