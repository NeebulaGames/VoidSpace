// All rights Neebula Games

#pragma once

#include "HighlightComponent.h"
#include "EquipableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMILA_API UEquipableComponent : public UHighlightComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipableAction);

public:	
	// Sets default values for this component's properties
	UEquipableComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	void Equipped();

	void Unequiped();

	void Fire() const;

	void EndFire() const;

public:

	UPROPERTY(BlueprintAssignable, Category = EquipableConfig)
	FOnEquipableAction OnEquipped;

	UPROPERTY(BlueprintAssignable, Category = EquipableConfig)
	FOnEquipableAction OnUnequipped;

	UPROPERTY(BlueprintAssignable, Category = EquipableConfig)
	FOnEquipableAction OnFire;

	UPROPERTY(BlueprintAssignable, Category = EquipableConfig)
	FOnEquipableAction OnEndFire;

	UPROPERTY(VisibleAnywhere, Category = EquipableConfig)
	FString Name;
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;		
	
};
