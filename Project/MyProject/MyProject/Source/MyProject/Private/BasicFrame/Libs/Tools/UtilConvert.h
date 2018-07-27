#pragma once

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilConvert
{
public:
	static std::string mConvRetStr;

public:
	static std::string& convInt2Str(int value);
	static int convStr2Int(std::string value);
	static std::string& convFloat2Str(float value);
	static std::string& convBool2Str(bool value);
};

MY_END_NAMESPACE