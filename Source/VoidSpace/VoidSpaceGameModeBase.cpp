// Fill out your copyright notice in the Description page of Project Settings.

#include "VoidSpace.h"
#include "VoidSpaceGameModeBase.h"
#include "SpaceCharacter.h"
#include "SpaceGameStateBase.h"


AVoidSpaceGameModeBase::AVoidSpaceGameModeBase(const FObjectInitializer& ObjectInitializer): AGameModeBase(ObjectInitializer)
{
	DefaultPawnClass = ASpaceCharacter::StaticClass();
	GameStateClass = ASpaceGameStateBase::StaticClass();
}

void AVoidSpaceGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
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
