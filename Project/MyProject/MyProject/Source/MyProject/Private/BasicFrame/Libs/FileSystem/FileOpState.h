#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class FileOpState
{
	eNoOp = 0,      // �޲���
	eOpening = 1,   // ����
	eOpenSuccess = 2,   // �򿪳ɹ�
	eOpenFail = 3,      // ��ʧ��
	eOpenClose = 4,     // �ر�
};

MY_END_NAMESPACE