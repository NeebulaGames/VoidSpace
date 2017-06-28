// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class VoidSpaceEditorTarget : TargetRules
{
	public VoidSpaceEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
	    ExtraModuleNames.Add("VoidSpace");
    }
}
