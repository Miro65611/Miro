// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MiroTarget : TargetRules
{
	public MiroTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("Miro");
		ExtraModuleNames.Add("MiroSessionModule");
		ExtraModuleNames.Add("MazeGeneratorModule");
    }
}
