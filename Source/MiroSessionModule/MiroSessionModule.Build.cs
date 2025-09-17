// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MiroSessionModule : ModuleRules
{
    public MiroSessionModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "OnlineSubsystem" });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
