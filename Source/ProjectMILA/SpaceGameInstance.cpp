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
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.bWaitForManualStop = true;

		//DeadLoadingScreen
		if (CurrentMapName == MapName && MapName == "/Game/Maps/SpaceStation")
		{
			LoadingScreen.WidgetLoadingScreen = SNew(SMainLoadingScreen);
		}
		//MenuLoadingScreen
		else
		{
			LoadingScreen.WidgetLoadingScreen = SNew(SMainLoadingScreen);
		}

		CurrentMapName = MapName;
	
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void USpaceGameInstance::EndLoadingScreen(UWorld* LoadedWorld)
{
}
