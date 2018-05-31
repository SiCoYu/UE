#ifndef __UtilLogic_H
#define __UtilLogic_H

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UtilLogic
{
public:
	static std::string convScenePath2LevelName(std::string& path);
};

MY_END_NAMESPACE

#endif