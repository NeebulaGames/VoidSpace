// All rights Neebula Games

#include "ProjectMILA.h"
#include "SMainLoadingScreen.h"
#include "MoviePlayer.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SThrobber.h"

SMainLoadingScreen::SMainLoadingScreen()
{
	NewTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("Texture2D'/Game/Textures/MainLoadingScreen.MainLoadingScreen'")));
	Font = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), NULL, TEXT("Font'/Game/Fonts/Proxima_Nova_Alt_Regular_Font.Proxima_Nova_Alt_Regular_Font'")));
}

void SMainLoadingScreen::Construct(const FArguments& InArgs)
{
	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Left)
			[
				SNew(SImage).Image(new FSlateDynamicImageBrush(NewTexture, FVector2D(1920, 1080), FName("LoadingScreen")))	
			]
			+ SOverlay::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(70.0f)
			[
				SNew(SThrobber)
					.Visibility(this, &SMainLoadingScreen::GetLoadIndicatorVisibility)
			]
			+ SOverlay::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(70.0f)
			[
				SNew(STextBlock)
					.Text(NSLOCTEXT("MoviePlayerTestLoadingScreen", "LoadingComplete", "Press any key to continue..."))
					.Font(FSlateFontInfo(Font, 18))
					.Visibility(this, &SMainLoadingScreen::GetMessageIndicatorVisibility)
			]
		];
}

EVisibility SMainLoadingScreen::GetLoadIndicatorVisibility() const
{
	return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
}

EVisibility SMainLoadingScreen::GetMessageIndicatorVisibility() const
{
	return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Visible : EVisibility::Collapsed;
}
