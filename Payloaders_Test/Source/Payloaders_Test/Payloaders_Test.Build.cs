// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Payloaders_Test : ModuleRules
{
	public Payloaders_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
			{ 
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"HeadMountedDisplay",
				"GameplayTasks"
			});
	}
}
