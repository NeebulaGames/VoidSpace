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

	UTexture2D* NewTexture;
	UFont* Font;
};
