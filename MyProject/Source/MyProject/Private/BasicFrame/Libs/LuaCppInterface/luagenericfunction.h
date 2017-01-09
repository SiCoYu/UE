#ifndef __LuaGenericFunction_H
#define __LuaGenericFunction_H

#include <functional>
#include "LuaFunctionBase.h"

template<typename T>
std::shared_ptr<T> LuaNoDestructor(T* obj)
{
	return std::shared_ptr<T>(obj, [](T*){});
}

#include "LuaGeneralGenericFunctions.h"
#include "LuaVoidGenericFunctions.h"

#endif // LUAGENERICFUNCTION_H
