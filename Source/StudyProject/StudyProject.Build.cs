// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StudyProject : ModuleRules
{
	public StudyProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"NavigationSystem", 
			"AIModule", 
			"GameplayTasks",
			"UMG",
			"Json"
		});
        PrivateDependencyModuleNames.AddRange(new string[]
        { 
            // Custom Modules
            "StudyProjectSettings",
        });
    }
}
