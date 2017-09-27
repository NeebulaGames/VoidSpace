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

private:

	FIntPoint ConvertSize(const UTexture2D* texture, float factor) const;

	EVisibility GetLoadIndicatorVisibility() const;
	EVisibility GetMessageIndicatorVisibility() const;

	UTexture2D* BackgroundImage;

	float ScaleFactor = 0.0f;

	FSlateDynamicImageBrush* GamepadBrush;
	FSlateDynamicImageBrush* KeyboardWASDBrush;
	FSlateDynamicImageBrush* KeyboardShiftBrush;
	FSlateDynamicImageBrush* KeyboardLeftControlSpaceBrush;
	FSlateDynamicImageBrush* KeyboardSpaceBrush;
	FSlateDynamicImageBrush* KeyboardEBrush;
	FSlateDynamicImageBrush* Mouse;
	FSlateDynamicImageBrush* MouseClick;

	UFont* Font;
};
