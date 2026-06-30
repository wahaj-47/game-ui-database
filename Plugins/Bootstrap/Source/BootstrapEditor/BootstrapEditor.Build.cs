// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BootstrapEditor : ModuleRules
{
    public BootstrapEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "CommonGame",
                "Bootstrap"
            }
        );
    }
}