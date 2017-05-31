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
  DSTE_OnOverlap  UMETA(DisplayName = "OnOverlap") 
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

	UPROPERTY(EditAnywhere, Category = EndedEvent, meta = (AllowPrivateAccess = "true")) 
	FString EventName; 
 
	void LockUnlockDoors();

	UPROPERTY(EditAnywhere, Category = DoorList, meta = (AllowPrivateAccess = "true"))
	TArray<AProximityDoor*> Doors;

	UFUNCTION()
	void OnOverlap(AActor* actor1, AActor* actor2);
		
	UFUNCTION()
	void UpdateDoors();
	
};
