#ifndef _LUA_DEBUG_H_
#define _LUA_DEBUG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lua/lua.h"
#include "lua/lobject.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
#include "lua/lstate.h"
#include "lua/lopcodes.h"

struct ld_data_ {
    struct ld_data_ *next;
    char fn[512];
    unsigned int line;
};
typedef struct ld_data_ ld_data;

struct ld_Info_ {
    lua_State *L;
    ld_data *data;
};
typedef struct ld_Info_ ld_Info;

extern ld_Info *ld_new(lua_State *L);
extern void ld_printstack(lua_State *L);

extern int ld_register(lua_State *L);

#endif