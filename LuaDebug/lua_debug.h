#ifndef _LUA_DEBUG_H_
#define _LUA_DEBUG_H_

#include <stdio.h>
#include "lua/lua.h"
#include "lua/lobject.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
#include "lua/lstate.h"
#include "lua/lopcodes.h"

extern void ld_init(lua_State *L);
extern void ld_printstack(lua_State *L);

extern int ld_register(lua_State *L);

#endif