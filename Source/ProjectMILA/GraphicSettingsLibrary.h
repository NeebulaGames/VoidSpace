// All rights Neebula Games

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GraphicSettingsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMILA_API UGraphicSettingsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Get a list of screen resolutions supported on this machine
	UFUNCTION(BlueprintPure, Category = "Video Settings")
	static bool GetSupportedScreenResolutions(TArray<FText>& resolutions, int& currentResolutionPos);

	// Changes the screen resolution to the desired size
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool ChangeScreenResolution(int width, int height, bool fullscreen);

	// Gets if VSync is enabled
	UFUNCTION(BlueprintPure, Category = "Video Settings")
	static bool IsVSyncEnabled(bool& VSync);

	// Sets if VSync is enabled
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool SetVSyncEnabled(bool VSync);

	// Saves the screen resolution
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool SetScreenResolution(int width, int height, bool fullscreen);

	// Gets if Full Screen is enabled
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool IsFullScreenEnabled(bool& fullscreen);

	// Gets all the quality settings
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool GetVideoQualitySettings(int32& AntiAliasing, int32& Effects, int32& PostProcess, int32& Resolution, int32& Shadow, int32& Texture, int32& ViewDistance);

	// Sets all the quality settings
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool SetVideoQualitySettings(int32 AntiAliasing, int32 Effects, int32 PostProcess, int32 Resolution, int32 Shadow, int32 Texture, int32 ViewDistance);
	
	// Checks if any configuration is dirty
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool IsDirty(bool& IsDirty);

	// Saves and applies the settings to disk
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool SaveVideoModeAndQuality();

	// Reverts the settings from disk
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool RevertVideoModeAndQuality();
	
private:
	// Try to get the GameUserSettings object from the engine
	static UGameUserSettings* GetGameUserSettings();
	
};
