// Fill out your copyright notice in the Description page of Project Settings.

#include "VoidSpace.h"
#include "VoidSpaceGameModeBase.h"
#include "SpaceCharacter.h"


AVoidSpaceGameModeBase::AVoidSpaceGameModeBase(const FObjectInitializer& ObjectInitializer): AGameModeBase(ObjectInitializer)
{
	DefaultPawnClass = ASpaceCharacter::StaticClass();
}
