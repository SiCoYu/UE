#ifndef __LuaCustomLoader_H_
#define __LuaCustomLoader_H_

/**
 * @brief æﬂÃÂ≤Œ’’ loadlib.c
 */
#include "lua.hpp"
#include <string>

void dotAddLoader(lua_State *L);
int dotLoadLua(lua_State *L);
int traceback(lua_State *L);
int mcheckload(lua_State *L, int stat, const char *filename);

#endif