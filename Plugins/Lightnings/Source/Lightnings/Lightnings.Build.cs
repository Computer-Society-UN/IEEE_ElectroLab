
using UnrealBuildTool;

public class Lightnings : ModuleRules
{
	public Lightnings(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "Niagara"
			});
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Engine", "CoreUObject"
				
			});
	}
}