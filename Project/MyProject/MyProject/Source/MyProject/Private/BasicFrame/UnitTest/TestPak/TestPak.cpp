#include "MyProject.h"
#include "TestPak.h"

#include "Containers/UnrealString.h"	// FString
#include "UtilEngineWrap.h"
#include "UtilFileIO.h"
#include "MPakFileSystem.h"
#include "Ctx.h"
#include "MySoftObjectPath.h"
#include "MyStreamableManager.h"

MY_BEGIN_NAMESPACE(MyNS)

void TestPak::run()
{
	FString pakFileFullPath = UtilFileIO::GameContentDir() + TEXT("OutPak.pak");
	FString mountPoint(UtilFileIO::EngineContentDir());

	MPakFileStream* pakFileStream = GPakFileSystem->mountOnePak(pakFileFullPath, mountPoint);
	MySoftObjectPath softObjectPath;
	softObjectPath.setPath();
	GMyStreamableManager->SynchronousLoad(softObjectPath.getNativeSoftObjectPath());
}

MY_END_NAMESPACE