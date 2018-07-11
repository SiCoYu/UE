#pragma once

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MConvert
{
public:
	std::string convInt2Str(int value);
	int convStr2Int(std::string value);
};

MY_END_NAMESPACE