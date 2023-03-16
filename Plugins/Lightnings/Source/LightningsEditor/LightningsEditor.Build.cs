
using UnrealBuildTool;

public class LightningsEditor : ModuleRules
{
	public LightningsEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "UnrealEd", "SlateCore", "Slate"
			});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Engine", "CoreUObject", nameof(Lightnings)
			});
	}
}
