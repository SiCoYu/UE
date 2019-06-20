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

MY_BEGIN_NAMESPACE(MyNS)

void TestPak::run()
{
	//GPakFileSystem->testLoadPak();

	//this->_testA();
	//this->_testB();
	this->_testC();
}

// 一个 pak 包一个资源
void TestPak::_testA()
{
	// 一定是相对目录，绝对目录是加载不了资源的
	//FString pakFileFullPath = UtilFileIO::ProjectContentDir(true) + TEXT("MyStreamingAssets/MultiOne.pak");
	FString pakFileFullPath = UtilFileIO::ProjectContentDir(false) + TEXT("MyStreamingAssets/Cube.pak");
	//FString mountPoint(UtilFileIO::EngineContentDir(true));
	FString mountPoint(UtilFileIO::EngineContentDir(false));
	//FString mountPoint(UtilFileIO::GameContentDir(false));

	MPakFileStream* pakFileStream = GPakFileSystem->mountOnePak(pakFileFullPath, mountPoint);

	MySoftObjectPath softObjectPath;

	softObjectPath.setPath(pakFileStream->getSoftPathStrByIndex(0));
	GMyStreamableManager->SynchronousLoad(softObjectPath.getNativeSoftObjectPath());

	GPakFileSystem->mountBaseFileSystem();
}

// 一个 pak 包多个资源
void TestPak::_testB()
{
	// 一定是相对目录，绝对目录是加载不了资源的
	//FString pakFileFullPath = UtilFileIO::ProjectContentDir(true) + TEXT("MyStreamingAssets/MultiOne.pak");
	FString pakFileFullPath = UtilFileIO::ProjectContentDir(false) + TEXT("MyStreamingAssets/MultiOne.pak");
	//FString mountPoint(UtilFileIO::EngineContentDir(true));
	FString mountPoint(UtilFileIO::EngineContentDir(false));
	//FString mountPoint(UtilFileIO::ProjectContentDir(false));

	MPakFileStream* pakFileStream = GPakFileSystem->mountOnePak(pakFileFullPath, mountPoint);

	MySoftObjectPath softObjectPath;

	softObjectPath.setPath(pakFileStream->getSoftPathStrByIndex(0));
	GMyStreamableManager->SynchronousLoad(softObjectPath.getNativeSoftObjectPath());

	softObjectPath.setPath(pakFileStream->getSoftPathStrByIndex(1));
	GMyStreamableManager->SynchronousLoad(softObjectPath.getNativeSoftObjectPath());

	GPakFileSystem->mountBaseFileSystem();
}

// 两个个 pak 包，每个包一个资源
void TestPak::_testC()
{
	// 一定是相对目录，绝对目录是加载不了资源的
	//FString pakFileFullPath = UtilFileIO::ProjectContentDir(true) + TEXT("MyStreamingAssets/MultiOne.pak");
	//FString pakFileFullPath = UtilFileIO::ProjectContentDir(false) + TEXT("MyStreamingAssets/MultiOne.pak");
	FString pakFileFullPath = UtilFileIO::ProjectContentDir(false) + TEXT("MyStreamingAssets/MyBlueprints/Cube.pak");
	//FString mountPoint(UtilFileIO::EngineContentDir(true));
	FString mountPoint(UtilFileIO::EngineContentDir(false));
	//FString mountPoint(UtilFileIO::ProjectContentDir(false));

	MPakFileStream* pakFileStream = GPakFileSystem->mountOnePak(pakFileFullPath, mountPoint);

	MySoftObjectPath softObjectPath;

	softObjectPath.setPath(pakFileStream->getSoftPathStrByIndex(0));
	GMyStreamableManager->SynchronousLoad(softObjectPath.getNativeSoftObjectPath());


	pakFileFullPath = UtilFileIO::ProjectContentDir(false) + TEXT("PakTest.pak");
	//FString mountPoint(UtilFileIO::EngineContentDir(true));
	mountPoint = UtilFileIO::EngineContentDir(false);
	//FString mountPoint(UtilFileIO::ProjectContentDir(false));

	pakFileStream = GPakFileSystem->mountOnePak(pakFileFullPath, mountPoint);

	MySoftObjectPath bSoftObjectPath;

	bSoftObjectPath.setPath(pakFileStream->getSoftPathStrByIndex(0));
	GMyStreamableManager->SynchronousLoad(bSoftObjectPath.getNativeSoftObjectPath());

	GPakFileSystem->mountBaseFileSystem();
}

MY_END_NAMESPACE