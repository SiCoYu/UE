#pragma once

#include "LoadItem.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 这个是从本地磁盘加载文本或者二进制文件
 */
class UBinaryLoadItem : public LoadItem
{
public:
	UBinaryLoadItem();
	virtual ~UBinaryLoadItem();

	void loadFile(const FString& Filename);
};

MY_END_NAMESPACE