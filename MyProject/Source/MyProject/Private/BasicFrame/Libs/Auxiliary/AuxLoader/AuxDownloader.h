#pragma once

#include "AuxLoaderBase.h"
#include <string>
#include "DownloadParam.h"
#include "EventDispatchDelegate.h"
#include "IDispatchObject.h"

namespace MyNS
{
    /**
     * @brief 下载
     */
    class AuxDownloader : AuxLoaderBase
    {
		typedef AuxLoaderBase Super;

	protected:
		DownloadItem* mDownloadItem;

		char* getBytes();
		// 下载一个资源
		virtual void download(std::string origPath, EventDispatchDelegate dispObj = nullptr, long fileLen = 0, bool isWriteFile = true, int downloadType = (int)eHttpWeb) override;
        // 下载完成
		void onDownloaded(IDispatchObject* dispObj);
	};
}