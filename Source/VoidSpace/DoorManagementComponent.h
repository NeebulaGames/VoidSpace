// All rights Neebula Games

#pragma once

#include "SpaceGameStateBase.h" 
#include "Components/ActorComponent.h"
#include "ProximityDoor.h"
#include "DoorManagementComponent.generated.h"

UENUM(BlueprintType)    //"BlueprintType" is essential to include 
enum class EDoorStartTriggerEnum : uint8 
{ 
  DSTE_OnBeginExecution   UMETA(DisplayName = "OnBeginExecution"), 
  DSTE_OnBeginEvent   UMETA(DisplayName = "OnBeginEvent"), 
  DSTE_OnOverlap  UMETA(DisplayName = "OnOverlap"),
  DSTE_OnDialogueFinished UMETA(DisplayName = "OnDialogueFinished"),
  DSTE_Deactivate  UMETA(DisplayName = "Deactivate")
}; 

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOIDSPACE_API UDoorManagementComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorManagementComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Execution)
	EDoorStartTriggerEnum StartTrigger; 

	UPROPERTY(EditAnywhere, Category = Execution)
	bool bOneShoot;

	UPROPERTY(EditAnywhere, Category = Execution)
	bool bOpenDoors;

	UPROPERTY(EditAnywhere, Category = Execution)
	bool bBlockDoors;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UGameEventManager* manager; 

	UPROPERTY(EditAnywhere, Category = Event, meta = (AllowPrivateAccess = "true")) 
	FString EventName; 

	UPROPERTY(EditAnywhere, Category = Event, meta = (AllowPrivateAccess = "true"))
	FString DialogueName;
 
	void LockUnlockDoors();

	UPROPERTY(EditAnywhere, Category = DoorList, meta = (AllowPrivateAccess = "true"))
	TArray<AProximityDoor*> Doors;

	UFUNCTION()
	void OnOverlap(AActor* actor1, AActor* actor2);
		
	UFUNCTION()
	void UpdateDoors();

	UFUNCTION()
	void UpdateOverlap();

	UFUNCTION()
	void OnDialogueCompleted(const FString& finishedDialogue);
};
