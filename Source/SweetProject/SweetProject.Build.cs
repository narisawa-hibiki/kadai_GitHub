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

        // ThirdParty�t�H���_�ւ̃x�[�X�p�X���擾
        var thirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/ASerial_Win"));

        // �w�b�_�t�@�C�����i�[����Ă���e�T�u�t�H���_�ւ̃p�X���ʂɒǉ�
        PrivateIncludePaths.Add(Path.Combine(thirdPartyPath, "ASerialCore"));
        PrivateIncludePaths.Add(Path.Combine(thirdPartyPath, "WindowsSerial"));

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
