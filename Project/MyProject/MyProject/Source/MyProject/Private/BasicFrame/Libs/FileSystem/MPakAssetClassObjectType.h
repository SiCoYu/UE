#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class MPakAssetClassObjectType
{
	eObject,		// ��Դ���ͣ����ص�ʱ����Ҫ�� "_C"
	eClass,			// BluePrint �����ͣ����ص�ʱ����Ҫ�� "_C",����  Pak ���м��� BluePrint ���Ϳ��Բ��� "_C" ������ԭʼ������� "_C" ������û�в��Թ� Pak ������Դ��������� "_C" �Ƿ���Լ��أ����Ŀǰ����ͳһ���ü� "_C"
};

MY_END_NAMESPACE