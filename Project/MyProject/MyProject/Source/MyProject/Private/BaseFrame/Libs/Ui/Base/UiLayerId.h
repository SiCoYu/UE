#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class UiLayerId
{
	eBtmLayer,                   // ��Ͳ㰡��һ�㲻�Ŷ������Ա���ʱ֮�裬Ŀǰ��ģ���Ľ���
	eFirstLayer,                 // ��һ�㣬����֮��������洰��
	eSecondLayer,                // �ڶ��㣬��Ҫ�ǹ����ԵĽ��棬������Ҫ�رյĽ���
	eThirdLayer,                 // �����㣬����������
	eForthLayer,                 // ���Ĳ㣬��ʾ���ڲ�
	eTopLayer,                   // ��㣬һ�㲻�Ŷ������Ա���ʱ֮��

	eMaxLayer
};

MY_END_NAMESPACE