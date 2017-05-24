// All rights Neebula Games

#pragma once

#include "Components/ActorComponent.h"
#include "EquipableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOIDSPACE_API UEquipableComponent : public USceneComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipableAction);

public:	
	// Sets default values for this component's properties
	UEquipableComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	void Trigger() const;

public:

	UPROPERTY(BlueprintAssignable, Category = EquipableConfig)
	FOnEquipableAction OnEquipableUsed;

	UPROPERTY(VisibleAnywhere, Category = EquipableConfig)
	FString Name;
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;		
	
};
