// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ProjectMILA : ModuleRules
{
	public ProjectMILA(ReadOnlyTargetRules ROTargetRules) : base(ROTargetRules)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "MoviePlayer", "MovieScene", "LevelSequence" });

        PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Json", "JsonUtilities", "RHI" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
