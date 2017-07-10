// All rights Neebula Games

#include "ProjectMILA.h"
#include "SMainLoadingScreen.h"
#include "MoviePlayer.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SThrobber.h"

SMainLoadingScreen::SMainLoadingScreen()
{
	//static ConstructorHelpers::FObjectFinder<UTexture2D> myImage(TEXT("Texture2D'/Game/Textures/MainLoadingScreen.MainLoadingScreen'"));
	NewTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("Texture2D'/Game/Textures/MainLoadingScreen.MainLoadingScreen'")));
	//NewTexture = myImage.Object;
}

void SMainLoadingScreen::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Center)
			[
				SNew(SImage).Image(new FSlateDynamicImageBrush(NewTexture, FVector2D(1920, 1080), FName("LoadingScreen")))				
			]
				+ SVerticalBox::Slot()
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
					.Text(NSLOCTEXT("MoviePlayerTestLoadingScreen", "LoadingComplete", "Loading complete!"))
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
