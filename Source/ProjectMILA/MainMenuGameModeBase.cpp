// All rights Neebula Games

#include "ProjectMILA.h"
#include "MainMenuGameModeBase.h"


AMainMenuGameModeBase::AMainMenuGameModeBase(const FObjectInitializer& ObjectInitializer)
	: AVoidSpaceGameModeBase(ObjectInitializer)
{
	//GameStateClass = AGameStateBase::StaticClass();

	static ConstructorHelpers::FObjectFinder<UClass> playerController(TEXT("Class'/Game/Blueprints/MenuPlayerController.MenuPlayerController_C'"));
	PlayerControllerClass = playerController.Object;

	DefaultPawnClass = APawn::StaticClass();
	HUDClass = AHUD::StaticClass();

	static ConstructorHelpers::FObjectFinder<UClass> startingWidget(TEXT("Class'/Game/Blueprints/MainMenu.MainMenu_C'"));
	StartingWidgetClass = startingWidget.Object;
}
