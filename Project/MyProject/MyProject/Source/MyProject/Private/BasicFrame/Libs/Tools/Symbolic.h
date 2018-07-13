#pragma once

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class Symbolic
{
public:
	static char CR;  // 13
	static char LF;  // 10

	static std::string CR_LF;       // �س����У� Mac ���漴ʹд�� "\r\n"����ȡ������Ҳֻ�� "\n"��������� Windows ��Ҳֻд�� "\n"�������� "\r\n"
	static std::string SEPARATOR;    // �ָ���
};

MY_END_NAMESPACE