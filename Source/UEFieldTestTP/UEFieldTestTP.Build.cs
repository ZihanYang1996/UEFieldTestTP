// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UEFieldTestTP : ModuleRules
{
	public UEFieldTestTP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
