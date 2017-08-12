static TAutoConsoleVariable<int32> MConsoleSys::CVarRefractionQuality(
    TEXT("r.RefractionQuality"),
    2,
    TEXT("Defines the distortion/refraction quality, adjust for quality or performance.\n")
    TEXT("<=0: off (fastest)\n")
    TEXT("  1: low quality (not yet implemented)\n")
    TEXT("  2: normal quality (default)\n")
    TEXT("  3: high quality (e.g. color fringe, not yet implemented)"),
    ECVF_Scalability | ECVF_RenderThreadSafe);

void MConsoleSys::registerConsoleVariable()
{
	IConsoleManager::Get().RegisterConsoleVariable(TEXT("r.RefractionQuality"),
	   2,
	   TEXT("Defines the distortion/refraction quality, adjust for quality or performance.\n")
		TEXT("<=0: off (fastest)\n")
		TEXT("  1: low quality (not yet implemented)\n")
		TEXT("  2: normal quality (default)\n")
		TEXT("  3: high quality (e.g. color fringe, not yet implemented)"),
	   ECVF_Scalability | ECVF_RenderThreadSafe);
}

void MConsoleSys::unregisterConsoleVariable()
{
	IConsoleManager::Get().UnregisterConsoleVariable(TEXT("r.RefractionQuality"));
}