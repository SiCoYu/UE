#pragma once

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ModulePath
{
public:
	static std::string LOGINMN;
    static std::string GAMEMN;
    static std::string AUTOUPDATEMN;
};

class ModuleName
{
public:
    static std::string LOGINMN;
    static std::string GAMEMN;
    static std::string AUTOUPDATEMN;
};

enum ModuleId
{
	LOGINMN,
	GAMEMN,
	AUTOUPDATEMN,
};

MY_END_NAMESPACE