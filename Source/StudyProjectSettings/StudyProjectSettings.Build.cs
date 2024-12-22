using UnrealBuildTool;

public class StudyProjectSettings : ModuleRules
{
    public StudyProjectSettings(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            // Initial Modules
            "Core", "CoreUObject", "Engine", "InputCore",
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

    }
}