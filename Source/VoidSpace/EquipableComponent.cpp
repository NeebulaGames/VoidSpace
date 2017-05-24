// All rights Neebula Games

#include "VoidSpace.h"
#include "EquipableComponent.h"


// Sets default values for this component's properties
UEquipableComponent::UEquipableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	BoxComponent->SetupAttachment(this);
	BoxComponent->InitBoxExtent(FVector(10));
	BoxComponent->bSelectable = false;
}

// Called when the game starts
void UEquipableComponent::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.bCanEverTick = false;
}

void UEquipableComponent::Equipped()
{
	SetActive(false);

	OnEquipped.Broadcast();
}

void UEquipableComponent::Unequiped()
{
	SetActive(true);

	OnUnequipped.Broadcast();
}

void UEquipableComponent::Trigger() const
{
	OnUsed.Broadcast();
}
