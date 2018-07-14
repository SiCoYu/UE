#include "MyProject.h"
#include "TestPak.h"

#include "Containers/UnrealString.h"	// FString
#include "UtilEngineWrap.h"
#include "UtilFileIO.h"
#include "MPakFileSystem.h"
#include "MPakFileStream.h"
#include "Ctx.h"
#include "MySoftObjectPath.h"
#include "MyStreamableManager.h"
#include "VersionSysN.h"

MY_BEGIN_NAMESPACE(MyNS)

void TestPak::run()
{
	GPakFileSystem->testLoadPak();

	FString pakFileFullPath = UtilFileIO::GameContentDir() + TEXT("MyAsset/Pak/MultiOne.pak");
	FString mountPoint(UtilFileIO::EngineContentDir());

	MPakFileStream* pakFileStream = GPakFileSystem->mountOnePak(pakFileFullPath, mountPoint);

	MySoftObjectPath softObjectPath;

	softObjectPath.setPath(pakFileStream->getSoftPathStrByIndex(0));
	GMyStreamableManager->SynchronousLoad(softObjectPath.getNativeSoftObjectPath());

	softObjectPath.setPath(pakFileStream->getSoftPathStrByIndex(1));
	GMyStreamableManager->SynchronousLoad(softObjectPath.getNativeSoftObjectPath());

	GPakFileSystem->mountBaseFileSystem();

	VersionSysN* a = MY_NEW VersionSysN();
}

MY_END_NAMESPACE