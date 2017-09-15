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

		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;

		if (MapName == "/Game/Maps/MainMenu")
		{
			// Play initial movie
			if (CurrentMapName == "")
			{
				LoadingScreen.MoviePaths.Add(TEXT("UE4_Moving_Logo_720"));
				// TODO: Add our movie
				LoadingScreen.bMoviesAreSkippable = false;
				LoadingScreen.bAllowInEarlyStartup = true;
				LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
			}
			// Standard menu loading
			else
			{
				LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
			}
		}
		//DeathLoadingScreen
		else if (CurrentMapName == MapName && MapName == "/Game/Maps/SpaceStation")
		{
			LoadingScreen.bWaitForManualStop = false;
			LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
		}
		// MenuLoadingScreen
		else
		{
			LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
			LoadingScreen.bWaitForManualStop = true;
			LoadingScreen.WidgetLoadingScreen = SNew(SMainLoadingScreen);
		}

		CurrentMapName = MapName;
	
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
		GetMoviePlayer()->PlayMovie();
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
