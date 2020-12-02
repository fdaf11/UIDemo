// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class UIModule : ModuleRules
{
	public UIModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
            "UMG",
            "Slate",
            "SlateCore",
            "WebBrowser",
            "WebBrowserWidget",
		}
		);

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}

