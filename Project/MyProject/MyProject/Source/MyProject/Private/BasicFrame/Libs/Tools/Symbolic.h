#pragma once

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class Symbolic
{
public:
	static char CR;  // 13
	static char LF;  // 10

	static std::string CR_LF;       // 回车换行， Mac 下面即使写入 "\r\n"，读取出来后，也只有 "\n"，因此这里 Windows 下也只写入 "\n"，而不是 "\r\n"
	static std::string SEPARATOR;    // 分隔符
};

MY_END_NAMESPACE