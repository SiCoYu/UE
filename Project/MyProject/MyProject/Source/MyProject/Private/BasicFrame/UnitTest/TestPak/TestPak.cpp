#include "MyProject.h"
#include "TestPak.h"

#include "Containers/UnrealString.h"	// FString
#include "UtilEngineWrap.h"
#include "UtilFileIO.h"
#include "MPakFileSystem.h"
#include "Ctx.h"

MY_BEGIN_NAMESPACE(MyNS)

void TestPak::run()
{
	FString pakFileFullPath = UtilFileIO::GameContentDir() + TEXT("OutPak.pak");
	FString mountPoint(UtilFileIO::EngineContentDir());

	GPakFileSystem->mountOnePak(pakFileFullPath, mountPoint);
}

MY_END_NAMESPACE