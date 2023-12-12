// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LobbyServer : ModuleRules
{
	public LobbyServer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "LobbyProtocol", "Networking", "OnlineSubsystemUtils" });

		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "Sockets"});
	}
}
