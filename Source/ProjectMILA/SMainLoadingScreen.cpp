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
	
	static UTexture2D* gamepadImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/Menus/ControlsScreen/ControlsGamepadWithText.ControlsGamepadWithText'")));
	static UTexture2D* keyboardWASD = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/Menus/ControlsScreen/ControlsKeyboardAWSD.ControlsKeyboardAWSD'")));
	static UTexture2D* keyboardSpace = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/Menus/ControlsScreen/ControlsKeyboardSpacebar.ControlsKeyboardSpacebar'")));
	static UTexture2D* keyboardShift = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/Menus/ControlsScreen/ControlsKeyboardShift.ControlsKeyboardShift'")));
	static UTexture2D* keyboardLeftControlSpace = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/Menus/ControlsScreen/ControlsKeyboardLeftCtrlAndSpacebar.ControlsKeyboardLeftCtrlAndSpacebar'")));
	static UTexture2D* keyboardE = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/Menus/ControlsScreen/ControlsKeyboardE.ControlsKeyboardE'")));
	static UTexture2D* mouse = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/Menus/ControlsScreen/ControlsMouse.ControlsMouse'")));
	static UTexture2D* mouseClick = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Textures/Menus/ControlsScreen/ControlsMouseClick.ControlsMouseClick'")));

	Font = Cast<UFont>(StaticLoadObject(UFont::StaticClass(), NULL, TEXT("Font'/Game/Fonts/Proxima_Nova_Alt_Regular_Font.Proxima_Nova_Alt_Regular_Font'")));

	ScaleFactor = 1990.f / GEngine->GameViewport->GetWindow()->GetSizeInScreen().X;

	GamepadBrush = new FSlateDynamicImageBrush(gamepadImage, ConvertSize(gamepadImage, ScaleFactor), FName("Gamepad"));
	GamepadBrush->DrawAs = ESlateBrushDrawType::Box;

	KeyboardWASDBrush = new FSlateDynamicImageBrush(keyboardWASD, ConvertSize(keyboardWASD, ScaleFactor), FName("WASD"));
	KeyboardWASDBrush->DrawAs = ESlateBrushDrawType::Box;

	KeyboardShiftBrush = new FSlateDynamicImageBrush(keyboardShift, ConvertSize(keyboardShift, ScaleFactor), FName("Shift"));
	KeyboardShiftBrush->DrawAs = ESlateBrushDrawType::Box;

	KeyboardLeftControlSpaceBrush = new FSlateDynamicImageBrush(keyboardLeftControlSpace, ConvertSize(keyboardLeftControlSpace, ScaleFactor), FName("LeftControlSpace"));
	KeyboardLeftControlSpaceBrush->DrawAs = ESlateBrushDrawType::Box;

	KeyboardSpaceBrush = new FSlateDynamicImageBrush(keyboardSpace, ConvertSize(keyboardSpace, ScaleFactor), FName("Space"));
	KeyboardSpaceBrush->DrawAs = ESlateBrushDrawType::Box;

	KeyboardEBrush = new FSlateDynamicImageBrush(keyboardE, ConvertSize(keyboardE, ScaleFactor), FName("E"));
	KeyboardEBrush->DrawAs = ESlateBrushDrawType::Box;

	Mouse = new FSlateDynamicImageBrush(mouse, ConvertSize(mouse, ScaleFactor), FName("Mouse"));
	Mouse->DrawAs = ESlateBrushDrawType::Box;

	MouseClick = new FSlateDynamicImageBrush(mouseClick, ConvertSize(mouseClick, ScaleFactor), FName("MouseClick"));
	MouseClick->DrawAs = ESlateBrushDrawType::Box;
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
				SNew(SImage).Image(new FSlateDynamicImageBrush(BackgroundImage, BackgroundImage->GetImportedSize(), FName("LoadingScreen")))
			]
			+ SOverlay::Slot()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Fill)
				.Padding(50.f, 0.f)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
					.VAlign(VAlign_Fill)
					.AutoHeight()
					.Padding(0.f, 70.f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot() // Keyboard and mouse
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Fill)
						.Padding(40.f, 0.f, 0.f, 0.f)
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
								.Font(FSlateFontInfo(Font, 24 / ScaleFactor))
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
									.HAlign(HAlign_Center)
									.Padding(0.f, 10.f)
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
										.AutoWidth()
									[
										SNew(SImage).Image(KeyboardWASDBrush)
									]
									+ SHorizontalBox::Slot()
										.VAlign(VAlign_Center)
										.Padding(10.f, 0.f)
									[
										SNew(STextBlock)
											.Text(LOCTEXT("WASD", "Movement"))
											.Font(FSlateFontInfo(Font, 20 / ScaleFactor))
									]
								]
								+ SVerticalBox::Slot()
									.AutoHeight()
									.HAlign(HAlign_Center)
									.Padding(0.f, 10.f)
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
										.AutoWidth()
									[
										SNew(SImage).Image(KeyboardShiftBrush)
									]
									+ SHorizontalBox::Slot()
										.VAlign(VAlign_Center)
										.Padding(10.f, 0.f)
									[
										SNew(STextBlock)
											.Text(LOCTEXT("Shift", "Sprint"))
											.Font(FSlateFontInfo(Font, 20 / ScaleFactor))
									]
								]
								+ SVerticalBox::Slot()
									.AutoHeight()
									.HAlign(HAlign_Center)
									.Padding(0.f, 10.f)
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
										.AutoWidth()
									[
										SNew(SImage).Image(KeyboardLeftControlSpaceBrush)
									]
									+ SHorizontalBox::Slot()
										.VAlign(VAlign_Center)
										.Padding(10.f, 0.f)
									[
										SNew(STextBlock)
											.Text(LOCTEXT("LeftControlSpace", "Go up and\ndown in\nthe space"))
											.Font(FSlateFontInfo(Font, 20 / ScaleFactor))
									]
								]
							]
							+ SHorizontalBox::Slot() // Right column
								.VAlign(VAlign_Top)
								.HAlign(HAlign_Right)
								.Padding(20.f, 0.f, 0.f, 0.f)
								.AutoWidth()
							[
								SNew(SVerticalBox)
								+ SVerticalBox::Slot()
									.AutoHeight()
									.HAlign(HAlign_Left)
									.Padding(0.f, 20.f)
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
										.AutoWidth()
									[
										SNew(SImage).Image(KeyboardSpaceBrush)
									]
									+ SHorizontalBox::Slot()
										.VAlign(VAlign_Center)
										.Padding(10.f, 0.f)
									[
										SNew(STextBlock)
											.Text(LOCTEXT("Space", "Jump"))
											.Font(FSlateFontInfo(Font, 20 / ScaleFactor))
									]
								]
								+ SVerticalBox::Slot()
									.AutoHeight()
									.HAlign(HAlign_Left)
									.Padding(0.f, 10.f)
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
										.AutoWidth()
									[
										SNew(SImage).Image(KeyboardEBrush)
									]
									+ SHorizontalBox::Slot()
										.VAlign(VAlign_Center)
										.Padding(10.f, 0.f)
									[
										SNew(STextBlock)
											.Text(LOCTEXT("E", "Interact"))
											.Font(FSlateFontInfo(Font, 20 / ScaleFactor))
									]
								]
								+ SVerticalBox::Slot()
									.AutoHeight()
									.HAlign(HAlign_Left)
									.Padding(0.f, 10.f)
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
										.AutoWidth()
									[
										SNew(SImage).Image(Mouse)
									]
									+ SHorizontalBox::Slot()
										.VAlign(VAlign_Center)
										.Padding(10.f, 0.f)
									[
										SNew(STextBlock)
											.Text(LOCTEXT("Mouse", "Camera"))
											.Font(FSlateFontInfo(Font, 20 / ScaleFactor))
									]
								]
								+ SVerticalBox::Slot()
									.AutoHeight()
									.HAlign(HAlign_Left)
									.Padding(0.f, 10.f)
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
										.AutoWidth()
									[
										SNew(SImage).Image(MouseClick)
									]
									+ SHorizontalBox::Slot()
										.VAlign(VAlign_Center)
										.Padding(10.f, 0.f)
									[
										SNew(STextBlock)
											.Text(LOCTEXT("MouseClick", "Use equipped object"))
											.Font(FSlateFontInfo(Font, 20 / ScaleFactor))
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
								.Font(FSlateFontInfo(Font, 24 / ScaleFactor))
						]
						+ SVerticalBox::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.Padding(0.f, 20.f)
							.AutoHeight()
						[
							SNew(SImage).Image(GamepadBrush)
						]
					]
				]
				+ SVerticalBox::Slot()
					.VAlign(VAlign_Bottom)
					.HAlign(HAlign_Center)
				[
					SNew(STextBlock)
						.Text(LOCTEXT("NoPause", "REMEMBER: In this game you CANNOT pause the action."))
						.Font(FSlateFontInfo(Font, 23 / ScaleFactor))
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
					.Font(FSlateFontInfo(Font, 18 / ScaleFactor))
					.Visibility(this, &SMainLoadingScreen::GetMessageIndicatorVisibility)
			]
		];
}

FIntPoint SMainLoadingScreen::ConvertSize(const UTexture2D* texture, float factor) const
{
	FIntPoint size = texture->GetImportedSize();
	return FIntPoint(FMath::FloorToInt(size.X / factor), FMath::FloorToInt(size.Y / factor));
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
