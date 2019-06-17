#include "MyProject.h"
#include "Prequisites.h"
#include "TestDownload.h"
#include "DownloadParam.h"

MY_BEGIN_NAMESPACE(MyNS)

void TestDownload::run()
{
	DownloadParam* downloadParam = MY_NEW DownloadParam();
	downloadParam->setPath("");
	GDownloadMgr->download(downloadParam);
	MY_SAFE_DISPOSE(downloadParam);
}

MY_END_NAMESPACE