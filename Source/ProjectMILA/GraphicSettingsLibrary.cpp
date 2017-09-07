// All rights Neebula Games

#include "ProjectMILA.h"
#include "GraphicSettingsLibrary.h"

bool UGraphicSettingsLibrary::GetSupportedScreenResolutions(TArray<FText>& resolutions, int& currentResolutionPos)
{
	FScreenResolutionArray resolutionsArray;
	UGameUserSettings* userSettings = GetGameUserSettings();
	int resolutionPos = currentResolutionPos = 0;
	if (userSettings && RHIGetAvailableResolutions(resolutionsArray, true))
	{
		FIntPoint currentResolution = userSettings->GetScreenResolution();
		for (const FScreenResolutionRHI& resolution : resolutionsArray)
		{
			const FString strW = FString::FromInt(resolution.Width);
			const FString strH = FString::FromInt(resolution.Height);

			if (currentResolution.X == resolution.Width && currentResolution.Y == resolution.Height)
			{
				currentResolutionPos = resolutionPos;
			}

			++resolutionPos;
			resolutions.Add(FText::FromString(strW + "x" + strH));
		}

		return true;
	}

	return false;
}

bool UGraphicSettingsLibrary::ChangeScreenResolution(int32 width, int32 height, bool fullscreen)
{
	UGameUserSettings* userSettings = GetGameUserSettings();

	if (!userSettings)
	{
		return false;
	}

	const EWindowMode::Type windowMode = fullscreen ? EWindowMode::Fullscreen : EWindowMode::Windowed;
	userSettings->RequestResolutionChange(width, height, windowMode, false);

	return true;
}

bool UGraphicSettingsLibrary::IsVSyncEnabled(bool& VSync)
{
	UGameUserSettings* userSettings = GetGameUserSettings();

	if (!userSettings)
	{
		return false;
	}

	VSync = userSettings->IsVSyncEnabled();

	return true;
}

bool UGraphicSettingsLibrary::SetVSyncEnabled(bool VSync)
{
	UGameUserSettings* userSettings = GetGameUserSettings();

	if (!userSettings)
	{
		return false;
	}

	userSettings->SetVSyncEnabled(VSync);

	return true;
}

bool UGraphicSettingsLibrary::SetScreenResolution(int width, int height, bool fullscreen)
{
	UGameUserSettings* userSettings = GetGameUserSettings();

	if (!userSettings)
	{
		return false;
	}

	const EWindowMode::Type windowMode = fullscreen ? EWindowMode::Fullscreen : EWindowMode::Windowed;
	userSettings->SetScreenResolution(FIntPoint(width, height));
	userSettings->SetFullscreenMode(windowMode);

	return true;
}

bool UGraphicSettingsLibrary::IsFullScreenEnabled(bool& fullscreen)
{
	UGameUserSettings* userSettings = GetGameUserSettings();

	if (!userSettings)
	{
		return false;
	}

	switch (userSettings->GetFullscreenMode())
	{
		case EWindowMode::Fullscreen:
			fullscreen = true;
			break;
		default:
			fullscreen = false;
			break;
	}

	return true;
}

bool UGraphicSettingsLibrary::GetVideoQualitySettings(int32& AntiAliasing, int32& Effects, int32& PostProcess,
	int32& Resolution, int32& Shadow, int32& Texture, int32& ViewDistance)
{
	UGameUserSettings* userSettings = GetGameUserSettings();

	if (!userSettings)
	{
		return false;
	}

	AntiAliasing = userSettings->ScalabilityQuality.AntiAliasingQuality;
	Effects = userSettings->ScalabilityQuality.EffectsQuality;
	PostProcess = userSettings->ScalabilityQuality.PostProcessQuality;
	Resolution = userSettings->ScalabilityQuality.ResolutionQuality;
	Shadow = userSettings->ScalabilityQuality.ShadowQuality;
	Texture = userSettings->ScalabilityQuality.TextureQuality;
	ViewDistance = userSettings->ScalabilityQuality.ViewDistanceQuality;

	return true;
}

bool UGraphicSettingsLibrary::SetVideoQualitySettings(int32 AntiAliasing, int32 Effects, int32 PostProcess,
	int32 Resolution, int32 Shadow, int32 Texture, int32 ViewDistance)
{
	UGameUserSettings* userSettings = GetGameUserSettings();

	if (!userSettings)
	{
		return false;
	}

	userSettings->ScalabilityQuality.AntiAliasingQuality = AntiAliasing;
	userSettings->ScalabilityQuality.PostProcessQuality = PostProcess;
	userSettings->ScalabilityQuality.ShadowQuality = Shadow;

	return true;
}

bool UGraphicSettingsLibrary::IsDirty(bool& IsDirty)
{
	UGameUserSettings* userSettings = GetGameUserSettings();

	if (!userSettings)
	{
		return false;
	}

	IsDirty = userSettings->IsDirty();

	return true;
}

bool UGraphicSettingsLibrary::SaveVideoModeAndQuality()
{
	UGameUserSettings* userSettings = GetGameUserSettings();
	
	if (!userSettings)
	{
		return false;
	}

	userSettings->ConfirmVideoMode();
	userSettings->ApplyNonResolutionSettings();
	userSettings->ApplySettings(false);
	return true;
}

bool UGraphicSettingsLibrary::RevertVideoModeAndQuality()
{
	UGameUserSettings* userSettings = GetGameUserSettings();

	if (!userSettings)
	{
		return false;
	}

	userSettings->RevertVideoMode();
	userSettings->ResetToCurrentSettings();

	return SaveVideoModeAndQuality();
}

UGameUserSettings* UGraphicSettingsLibrary::GetGameUserSettings()
{
	if (GEngine)
	{
		return GEngine->GameUserSettings;
	}

	return nullptr;
}
