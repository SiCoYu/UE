#pragma once

#include "AuxLoaderBase.h"
#include <string>
#include "DownloadParam.h"
#include "EventDispatchDelegate.h"
#include "IDispatchObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "TypeDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class DownloadItem;

/**
 * @brief 下载
 */
class AuxDownloader : public AuxLoaderBase
{
	M_DECLARE_CLASS(AuxDownloader, AuxLoaderBase)

protected:
	DownloadItem* mDownloadItem;

public:
	char* getBytes();

	// 下载一个资源
	virtual void download(
		std::string origPath, 
		EventDispatchDelegate dispObj = EventDispatchDelegate(),
		long fileLen = 0, 
		bool isWriteFile = true, 
		int downloadType = (int)DownloadType::eHttpWeb
	) override;
    // 下载完成
	void onDownloaded(uint eventId, IDispatchObject* dispObj);

	void setVersion(std::string version);
	void setIsNeedUncompress(bool value);
};

MY_END_NAMESPACE