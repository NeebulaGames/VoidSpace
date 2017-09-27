// All rights Neebula Games

#include "ProjectMILA.h"
#include "SMainLoadingScreen.h"
#include "MoviePlayer.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SThrobber.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
#define LOCTEXT_NAMESPACE "ControlsLoadingScreen" 

SMainLoadingScreen::SMainLoadingScreen()
{
	BackgroundImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/Menus/ControlsScreen/ControlsBackground.ControlsBackground'")));
	GamepadImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/Menus/ControlsScreen/ControlsGamepadWithText.ControlsGamepadWithText'")));
	KeyboardWASD = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/Menus/ControlsScreen/ControlsKeyboardAWSD.ControlsKeyboardAWSD'")));
	KeyboardSpace = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/Menus/ControlsScreen/ControlsKeyboardSpacebar.ControlsKeyboardSpacebar'")));
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
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
			[
				SNew(SImage).Image(new FSlateDynamicImageBrush(BackgroundImage, FVector2D(1920, 1080), FName("LoadingScreen")))
			]
			+ SOverlay::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
					.VAlign(VAlign_Fill)
					.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot() // Keyboard and mouse
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						.AutoWidth()
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot() // Title
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Top)
							.AutoHeight()
						[
							SNew(STextBlock)
								.Text(LOCTEXT("KeyboardMouse", "KEYBOARD/MOUSE"))
								.Font(FSlateFontInfo(Font, 24))
						]
						+ SVerticalBox::Slot()
							.VAlign(VAlign_Top)
							.HAlign(HAlign_Left)
						[
							SNew(SHorizontalBox) // Left column
							+ SHorizontalBox::Slot()
								.VAlign(VAlign_Top)
								.HAlign(HAlign_Left)
								.AutoWidth()
							[
								SNew(SVerticalBox)
								+ SVerticalBox::Slot()
									.AutoHeight()
									.HAlign(HAlign_Left)
									.Padding(20.f, 0.f)
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
										.AutoWidth()
									[
										SNew(SImage).Image(new FSlateDynamicImageBrush(KeyboardWASD, FVector2D(180.f, 135.f), FName("WASD")))
									]
									+ SHorizontalBox::Slot()
										.VAlign(VAlign_Center)
										.Padding(10.f, 0.f)
									[
										SNew(STextBlock)
											.Text(LOCTEXT("WASD", "Movement"))
											.Font(FSlateFontInfo(Font, 20))
									]
								]
							]
							+ SHorizontalBox::Slot() // Right column
								.VAlign(VAlign_Top)
								.HAlign(HAlign_Right)
								.AutoWidth()
							[
								SNew(SVerticalBox)
								+ SVerticalBox::Slot()
									.AutoHeight()
									.HAlign(HAlign_Left)
									.Padding(20.f, 20.f)
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
										.AutoWidth()
									[
										SNew(SImage).Image(new FSlateDynamicImageBrush(KeyboardSpace, FVector2D(180.f, 90.f), FName("WASD")))
									]
									+ SHorizontalBox::Slot()
										.VAlign(VAlign_Center)
									[
										SNew(STextBlock)
											.Text(LOCTEXT("Space", "Jump"))
											.Font(FSlateFontInfo(Font, 20))
									]
								]
							]
						]
					]
					+ SHorizontalBox::Slot() // Controller
						.HAlign(HAlign_Right)
						.Padding(10.f, 0.f)
					[
						SNew(SVerticalBox) // Title
						+ SVerticalBox::Slot()
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Top)
							.AutoHeight()
						[
							SNew(STextBlock)
								.Text(LOCTEXT("Gamepad", "GAMEPAD"))
								.Font(FSlateFontInfo(Font, 24))
						]
						+ SVerticalBox::Slot()
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Fill)
							.AutoHeight()
						[
							SNew(SImage).Image(new FSlateDynamicImageBrush(GamepadImage, FVector2D(939.f, 527.f) / 1.5f, FName("Gamepad")))
						]
					]
				]
				+ SVerticalBox::Slot()
					.VAlign(VAlign_Bottom)
					.HAlign(HAlign_Center)
				[
					SNew(STextBlock)
						.Text(LOCTEXT("NoPause", "REMEMBER: In this game you CANNOT pause the action."))
						.Font(FSlateFontInfo(Font, 23))
				]
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

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
