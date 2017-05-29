// All rights Neebula Games

#pragma once

#include "GameEventManager.h"
#include "GameFramework/Actor.h"
#include "UpdaterDoorsActor.generated.h"

UCLASS()
class VOIDSPACE_API AUpdaterDoorsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUpdaterDoorsActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = DoorManagement, meta = (AllowPrivateAccess = "true"))
	class UDoorManagementComponent* DoorManagementComponent;

	UPROPERTY(EditAnywhere, Category = EndedEvent, meta = (AllowPrivateAccess = "true"))
	FString EndedEventName;

	UFUNCTION()
	void UpdateDoors();

	UGameEventManager* manager;
};
