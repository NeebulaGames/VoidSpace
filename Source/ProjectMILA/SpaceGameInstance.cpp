// All rights Neebula Games

#include "ProjectMILA.h"
#include "SpaceGameInstance.h"
#include "MoviePlayer.h"

#include "SMainLoadingScreen.h"


void USpaceGameInstance::Init()
{
	UGameInstance::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &USpaceGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &USpaceGameInstance::EndLoadingScreen);
}

void USpaceGameInstance::BeginLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer())
	{
		FLoadingScreenAttributes LoadingScreen;

		//DeadLoadingScreen
		if (CurrentMapName == "" || CurrentMapName == MapName && MapName == "/Game/Maps/SpaceStation")
		{
			// replace this with a new dead Slate in the future.
			LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
			LoadingScreen.bWaitForManualStop = false;
			LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
		}
		//MenuLoadingScreen
		else
		{
			LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
			LoadingScreen.bWaitForManualStop = true;
			LoadingScreen.WidgetLoadingScreen = SNew(SMainLoadingScreen);
		}

		CurrentMapName = MapName;
	
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void USpaceGameInstance::EndLoadingScreen(UWorld* LoadedWorld)
{
}
