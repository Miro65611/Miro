// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MazeEditorModule : ModuleRules
{
    public MazeEditorModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "MazeGeneratorModule" });

        PrivateDependencyModuleNames.AddRange(new string[]
        {    "Slate",
            "SlateCore",
            "InputCore",
            "PropertyEditor",
             "ToolMenus",
            "UnrealEd" });
    }
}
