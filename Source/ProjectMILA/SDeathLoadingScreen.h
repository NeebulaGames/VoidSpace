// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include <SpaceStatics.h>

/**
 * 
 */
class PROJECTMILA_API SDeathLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDeathLoadingScreen)
	{}
		SLATE_ARGUMENT(EDeathReason, DeathReason)
	SLATE_END_ARGS()

	SDeathLoadingScreen();

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	EVisibility GetLoadIndicatorVisibility() const;
	EVisibility GetMessageIndicatorVisibility() const;

private:
	FText GetDeathText() const;

	EDeathReason DeathReason = EDeathReason::None;
	UTexture2D* Logo;
	UFont* Font;
};
