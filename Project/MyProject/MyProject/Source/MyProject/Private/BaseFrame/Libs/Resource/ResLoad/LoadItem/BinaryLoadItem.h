#pragma once

#include "LoadItem.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief ����Ǵӱ��ش��̼����ı����߶������ļ�
 */
class UBinaryLoadItem : public LoadItem
{
public:
	UBinaryLoadItem();
	virtual ~UBinaryLoadItem();

	void loadFile(const FString& Filename);
};

MY_END_NAMESPACE