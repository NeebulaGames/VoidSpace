// All rights Neebula Games

#include "ProjectMILA.h"
#include "SpaceGameInstance.h"
#include "MoviePlayer.h"

#include "SMainLoadingScreen.h"
#include "SDeathLoadingScreen.h"


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

		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		if (MapName == "/Game/Maps/MainMenu")
		{
			// TODO: Add movie
			// Play initial movie
			if (CurrentMapName == "")
			{
				LoadingScreen.bWaitForManualStop = false;
				LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
			}
			// Standard menu loading
			else
			{
				LoadingScreen.bWaitForManualStop = false;
				LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
			}
		}
		//DeathLoadingScreen
		else if (CurrentMapName == MapName && MapName == "/Game/Maps/SpaceStation")
		{
			// replace this with a new dead Slate in the future.
			LoadingScreen.bWaitForManualStop = true;
			LoadingScreen.WidgetLoadingScreen = SNew(SDeathLoadingScreen).DeathReason(LastDeathReason);
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

void USpaceGameInstance::ResetStats()
{
	LastDeathReason = EDeathReason::None;
	Retries = 0.f;
}
