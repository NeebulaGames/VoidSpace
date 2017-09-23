// All rights Neebula Games

#include "ProjectMILA.h"
#include "TributePickableComponent.h"

UTributePickableComponent::UTributePickableComponent()
	: UPickableComponent()
{
	bIgnorePlayerCollision = false;
	HighlightColor = EHighlightColor::Blue;

	static ConstructorHelpers::FObjectFinder<USoundWave> pachimariSound(TEXT("SoundWave'/Game/Sounds/SFX/Pachimari.Pachimari'"));
	PachimariSound = pachimariSound.Object;
}


void UTributePickableComponent::PickedUp()
{
	UGameplayStatics::PlaySound2D(GetWorld(), PachimariSound);
}
