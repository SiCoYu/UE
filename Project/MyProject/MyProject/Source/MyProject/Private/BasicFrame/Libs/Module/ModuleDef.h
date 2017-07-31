#pragma once

#include <string>

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