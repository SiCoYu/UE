#include "MyProject.h"
#include "Prequisites.h"
#include "TestDownload.h"
#include "DownloadParam.h"

void TestDownload::run()
{
	DownloadParam* downloadParam = MY_NEW DownloadParam();
	downloadParam->setPath("");
	GDownloadMgr->download(downloadParam);
	MY_DELETE downloadParam;
}