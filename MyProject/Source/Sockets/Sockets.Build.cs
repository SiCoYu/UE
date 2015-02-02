// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class MySockets : ModuleRules
{
	public MySockets(TargetInfo Target)
	{
		Type = ModuleType.External;

		string SocketsPath = UEBuildConfiguration.UEThirdPartySourceDirectory + "Sockets/Sockets-2.3.9.9/";

		PublicIncludePaths.Add(SocketsPath);

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicLibraryPaths.Add(SocketsPath + "Lib/Win64");
			PublicAdditionalLibraries.Add("Sockets.lib");
		}
    }
}
