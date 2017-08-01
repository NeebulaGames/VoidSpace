// All rights Neebula Games

#include "ProjectMILA.h"
#include "SDeathLoadingScreen.h"
#include "SlateOptMacros.h"
#include "MoviePlayer.h"
#include "SThrobber.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
#define LOCTEXT_NAMESPACE "DeathLoadingScreen" 

SDeathLoadingScreen::SDeathLoadingScreen()
{
	Font = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), nullptr, TEXT("Font'/Game/Fonts/Proxima_Nova_Alt_Regular_Font.Proxima_Nova_Alt_Regular_Font'")));

	Logo = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/HUD/LogoLoadingScreen.LogoLoadingScreen'")));
}

void SDeathLoadingScreen::Construct(const FArguments& InArgs)
{
	DeathReason = InArgs._DeathReason;
	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SImage).Image(new FSlateDynamicImageBrush(Logo, FVector2D(700, 210.4), FName("ProjectMILA_Logo")))
				]
				+ SVerticalBox::Slot()
				.Padding(0.f, 70.f)
				[
					SNew(SBox)
					.MinDesiredWidth(700)
					.MaxDesiredWidth(700)
					.VAlign(VAlign_Center)
					[
						SNew(SBorder)
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Fill)
						.BorderBackgroundColor(FColor::White)
						[
							SNew(SVerticalBox)
							+ SVerticalBox::Slot()
							.Padding(20.f)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("Diagnostic", "Diagnostic:"))
								.Font(FSlateFontInfo(Font, 18))
							]
							+ SVerticalBox::Slot()
							.Padding(20.f, 0.f, 20.f, 20.f)
							[
								SNew(STextBlock)
								.Text(this, &SDeathLoadingScreen::GetDeathText)
								.Font(FSlateFontInfo(Font, 18))
							]
						]
					]
				]
			]
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

FText SDeathLoadingScreen::GetDeathText() const
{
	
	switch (DeathReason)
	{
	case EDeathReason::Meteor: 
		return LOCTEXT("ShieldsNotActive", "Shields weren't activated");
	case EDeathReason::Choke: 
		return LOCTEXT("LeakNotFixed", "Leak wasn't fixed");
	case EDeathReason::ChokeSpacesuit:
		return LOCTEXT("NoMoreOxygen", "There wasn't any oxygen left in the spacesuit");
	default: 
		return LOCTEXT("UnknownReason", "Unknown reason...");
	}
}

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
