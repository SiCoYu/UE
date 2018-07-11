#pragma once

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilConvert
{
public:
	std::string convInt2Str(int value);
	int convStr2Int(std::string value);
};

MY_END_NAMESPACE