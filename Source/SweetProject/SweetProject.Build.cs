// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class SweetProject : ModuleRules
{
	public SweetProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // ThirdPartyフォルダへのベースパスを取得
        var thirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/ASerial_Win"));

        // ヘッダファイルが格納されている各サブフォルダへのパスを個別に追加
        PrivateIncludePaths.Add(Path.Combine(thirdPartyPath, "ASerialCore"));
        PrivateIncludePaths.Add(Path.Combine(thirdPartyPath, "WindowsSerial"));

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
