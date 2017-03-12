// All rights Neebula Games

#include "VoidSpace.h"
#include "SpaceGameStateBase.h"
#include "SpaceCharacter.h"

void ASpaceGameStateBase::TogglePlayerGravity() const
{
	ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (character)
	{
		character->ToggleGravity();
	}
}

void ASpaceGameStateBase::ToggleSpaceSuit(bool activate) const
{
	ASpaceCharacter* character = Cast<ASpaceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (character)
	{
		character->ToggleSpaceSuit(activate);
	}
}

ASpaceGameStateBase* ASpaceGameStateBase::Instance(UObject* world)
{
	return Cast<ASpaceGameStateBase>(UGameplayStatics::GetGameState(world));
}
