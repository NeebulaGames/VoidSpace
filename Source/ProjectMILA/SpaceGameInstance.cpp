// All rights Neebula Games

#include "ProjectMILA.h"
#include "SpaceGameInstance.h"
#include "MoviePlayer.h"


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
		LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void USpaceGameInstance::EndLoadingScreen(UWorld* LoadedWorld)
{
}
