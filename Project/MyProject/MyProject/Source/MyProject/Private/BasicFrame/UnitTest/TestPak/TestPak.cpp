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
	//GPakFileSystem->testLoadPak();

	// 一定是相对目录，绝对目录是加载不了资源的
	//FString pakFileFullPath = UtilFileIO::GameContentDir(true) + TEXT("MyStreamingAssets/MultiOne.pak");
	//FString mountPoint(UtilFileIO::EngineContentDir(true));
	FString pakFileFullPath = UtilFileIO::GameContentDir(false) + TEXT("MyStreamingAssets/MultiOne.pak");
	//FString mountPoint(UtilFileIO::EngineContentDir(false));
	FString mountPoint(UtilFileIO::GameContentDir(false));

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