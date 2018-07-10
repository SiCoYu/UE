#pragma once

#include <string>
#include "ResLoadType.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class FileVerInfo;

/**
 *@brief 资源重定向 Item
 */
class ResRedirectItem
{
public:
	std::string mOrigPath;             // 资源原始目录，就是逻辑加载资源的目录
    ResLoadType mResLoadType;        // 资源目录
    FileVerInfo* mFileVerInfo;        // 文件的基本信息

public:
	ResRedirectItem(std::string origPath = "", int redirect = (int)ResLoadType.eLoadResource);

	bool isRedirectR();
	bool isRedirectS();
	bool isRedirectP();
	bool isRedirectW();
};

MY_END_NAMESPACE