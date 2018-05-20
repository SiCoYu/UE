#include "MyProject.h"
#include "Prequisites.h"
#include "TestDownload.h"
#include "DownloadParam.h"

void TestDownload::run()
{
	DownloadParam* downloadParam = new DownloadParam();
	downloadParam->setPath("");
	GDownloadMgr->download(downloadParam);
	delete downloadParam;
}