#pragma once

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MYPROJECT_API ModulePath
{
public:
	static std::string LOGINMN;
    static std::string GAMEMN;
    static std::string AUTOUPDATEMN;
};

class MYPROJECT_API ModuleName
{
public:
    static std::string LOGINMN;
    static std::string GAMEMN;
    static std::string AUTOUPDATEMN;
};

MY_END_NAMESPACE