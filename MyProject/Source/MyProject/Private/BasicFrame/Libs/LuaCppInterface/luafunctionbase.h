#ifndef __LuaFunctionBase_H
#define __LuaFunctionBase_H

#include <string>

#include "LuaReference.h"

class LuaFunctionBase : public LuaReference
{
public:
	LuaFunctionBase(std::shared_ptr<lua_State> state, int index);
};

#endif // LUAFUNCTIONBASE_H
