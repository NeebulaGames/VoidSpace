// All rights Neebula Games

#pragma once

#include "MoviePlayer.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class PROJECTMILA_API SMainLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainLoadingScreen) {}
	SLATE_END_ARGS()

	SMainLoadingScreen();

	void Construct(const FArguments& InArgs);

	EVisibility GetLoadIndicatorVisibility() const;
	EVisibility GetMessageIndicatorVisibility() const;

	UTexture2D* BackgroundImage;
	UTexture2D* GamepadImage;
	UTexture2D* KeyboardWASD;
	UTexture2D* KeyboardSpace;
	UTexture2D* KeyboardShift;
	UTexture2D* KeyboardLeftControlSpace;
	UFont* Font;
};
