// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class Sockets : ModuleRules
{
	public Sockets(TargetInfo Target)
	{
		Type = ModuleType.External;

		string SocketsPath = UEBuildConfiguration.UEThirdPartySourceDirectory + "Sockets/Sockets-2.3.9.9/";

		PublicIncludePaths.Add(SocketsPath);

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicLibraryPaths.Add(SocketsPath + "Lib/Win64");
			PublicAdditionalLibraries.Add("zlib_64.lib");
		}
    }
}
