 // Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MiroEditorTarget : TargetRules
{
	public MiroEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("Miro");
        ExtraModuleNames.Add("MiroSessionModule");
        ExtraModuleNames.Add("MazeGeneratorModule");
        ExtraModuleNames.Add("MazeEditorModule");

    }
}
