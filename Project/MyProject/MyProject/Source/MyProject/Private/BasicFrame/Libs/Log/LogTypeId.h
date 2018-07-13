#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class LogTypeId
{
	eLogCommon,         // ͨ����־
	eLogDataStruct,		// ���ݽṹ��־
	eLogPriorityListCheck,
	eLogNoPriorityListCheck, 
	eLogDownload,		// ����
	eLogAutoUpdate,
	eLogResLoader,
	eErrorDownload,
};

MY_END_NAMESPACE