#include "MyProject.h"
#include "MConsoleSys.h"

static TAutoConsoleVariable<int32> UMConsoleSys::CVarRefractionQuality(
    TEXT("r.RefractionQuality"),
    2,
    TEXT("Defines the distortion/refraction quality, adjust for quality or performance.\n")
    TEXT("<=0: off (fastest)\n")
    TEXT("  1: low quality (not yet implemented)\n")
    TEXT("  2: normal quality (default)\n")
    TEXT("  3: high quality (e.g. color fringe, not yet implemented)"),
    ECVF_Scalability | ECVF_RenderThreadSafe);

UMConsoleSys::UMConsoleSys(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UMConsoleSys::registerConsoleVariable()
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

void UMConsoleSys::unregisterConsoleVariable()
{
	IConsoleManager::Get().UnregisterConsoleVariable(TEXT("r.RefractionQuality"));
}