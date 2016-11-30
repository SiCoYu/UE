#pragma once

#include "LoadItem.h"

/**
 * @brief 这个是从本地磁盘加载文本或者二进制文件
 */
class UBinaryLoadItem : public LoadItem
{
public:
	void loadFile(const FString& Filename);
};