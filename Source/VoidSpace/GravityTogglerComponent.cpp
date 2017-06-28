// All rights Neebula Games

#include "VoidSpace.h"
#include "GravityTogglerComponent.h"
#include "SpaceGameStateBase.h"


// Sets default values for this component's properties
UGravityTogglerComponent::UGravityTogglerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UGravityTogglerComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UGravityTogglerComponent::OnOverlap);
}

void UGravityTogglerComponent::OnOverlap(AActor* actor1, AActor* actor2)
{
	ASpaceGameStateBase* state = Cast<ASpaceGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

	if (state && actor2 == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Toggling gravity"));

		state->TogglePlayerGravity();
	}
}
