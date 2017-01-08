#ifndef __MyLuaLoader_H_
#define __MyLuaLoader_H_

/**
 * @brief æﬂÃÂ≤Œ’’ loadlib.c
 */
#include "lua.hpp"
#include <string>

void dotAddLoader(lua_State *L);
int dotLoadLua(lua_State *L);
int traceback(lua_State *L);
int checkResult(lua_State *L, int stat, const char *filename);

#endif