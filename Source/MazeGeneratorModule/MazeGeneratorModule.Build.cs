// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MazeGeneratorModule : ModuleRules
{
    public MazeGeneratorModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
