#pragma once

#include "LoadItem.h"

/**
 * @brief ����Ǵӱ��ش��̼����ı����߶������ļ�
 */
class UBinaryLoadItem : public LoadItem
{
public:
	void loadFile(const FString& Filename);
};