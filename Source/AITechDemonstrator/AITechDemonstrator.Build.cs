// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AITechDemonstrator : ModuleRules
{
	public AITechDemonstrator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"GameplayAbilities", 
			"GameplayTasks", 
			"GameplayTags",
			"GameFeatures"
		});

		PublicIncludePaths.AddRange(new string[]
		{ 
			"./AITechDemonstrator/Public",
            "./AITechDemonstrator/Public/PNN",
            "./AITechDemonstrator/Public/Misc",
            "./AITechDemonstrator/Public/Pawns",
            "./AITechDemonstrator/Public/Input",
            "./AITechDemonstrator/Public/Cameras",
            "./AITechDemonstrator/Public/Abilities",
            "./AITechDemonstrator/Public/Attributes",
            "./AITechDemonstrator/Public/Controllers",
            "./AITechDemonstrator/Public/GameFeatureActions",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
