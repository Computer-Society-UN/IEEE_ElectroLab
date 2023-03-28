// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class IEEE_ElectroLab : ModuleRules
{
	public IEEE_ElectroLab(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "UMG", "CommonUI", "SlateCore", "EnhancedInput"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
        {
        	"AsyncLoadingScreen",
        	"OnlineSubsystem",
        	"OnlineSubsystemUtils"
        });

		PrivateIncludePaths.Add("IEEE_ElectroLab");
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
