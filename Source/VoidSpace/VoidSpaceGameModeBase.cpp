// Fill out your copyright notice in the Description page of Project Settings.

#include "VoidSpace.h"
#include "VoidSpaceGameModeBase.h"
#include "SpaceCharacter.h"
#include "SpaceGameStateBase.h"
#include "ProximityDoor.h"


AVoidSpaceGameModeBase::AVoidSpaceGameModeBase(const FObjectInitializer& ObjectInitializer): AGameModeBase(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UClass> hudBlueprint(TEXT("Class'/Game/Blueprints/CrosshairHUD.CrosshairHUD_C'"));

	DefaultPawnClass = ASpaceCharacter::StaticClass();
	GameStateClass = ASpaceGameStateBase::StaticClass();
	HUDClass = hudBlueprint.Object;
}

void AVoidSpaceGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);

	//EXAMPLE TO CONTROL DOORS. REMOVE IT IN THE FUTURE (and the ProximityDoor.h include)
	//TActorIterator<AProximityDoor> DoorItr = TActorIterator<AProximityDoor>(GetWorld());
	//while (DoorItr)
	//{
	//	if(DoorItr->GetName().Equals("Door") || DoorItr->GetName().Equals("Door_1"))
	//		DoorItr->Lock();
	//	if(DoorItr->GetName().Equals("Door_9"))
	//	{
	//		DoorItr->OpenDoor();
	//		DoorItr->Lock();
	//	}
	//	++DoorItr;
	//}
}

void AVoidSpaceGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
