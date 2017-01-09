#ifndef __LuaError_H
#define __LuaError_H

#include "LuaCppInclude.h"

#include <exception>
#include <string>

class LuaError : public std::exception
{
	std::string msg;
public:
	LuaError(std::string msg) : msg(msg)
	{

	}

	~LuaError() throw()
	{

	}

	const std::string& GetMessage() const
	{
		return msg;
	}
};

std::string LuaGetLastError(lua_State* state);

#endif // LUACPPERROR