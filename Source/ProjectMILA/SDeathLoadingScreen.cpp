// All rights Neebula Games

#include "ProjectMILA.h"
#include "SDeathLoadingScreen.h"
#include "SlateOptMacros.h"
#include "MoviePlayer.h"
#include "SThrobber.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

SDeathLoadingScreen::SDeathLoadingScreen()
{
	Font = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), nullptr, TEXT("Font'/Game/Fonts/Proxima_Nova_Alt_Regular_Font.Proxima_Nova_Alt_Regular_Font'")));

	Logo = nullptr;
}

void SDeathLoadingScreen::Construct(const FArguments& InArgs)
{
	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			.Padding(70.0f)
			[
				SNew(SThrobber)
				.Visibility(this, &SDeathLoadingScreen::GetLoadIndicatorVisibility)
			]
			+ SOverlay::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			.Padding(70.0f)
			[
				SNew(STextBlock)
				.Text(NSLOCTEXT("MoviePlayerTestLoadingScreen", "LoadingComplete", "Press any key to continue..."))
				.Font(FSlateFontInfo(Font, 18))
				.Visibility(this, &SDeathLoadingScreen::GetMessageIndicatorVisibility)
			]
		];
}

EVisibility SDeathLoadingScreen::GetLoadIndicatorVisibility() const
{
	return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
}

EVisibility SDeathLoadingScreen::GetMessageIndicatorVisibility() const
{
	return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Visible : EVisibility::Collapsed;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
