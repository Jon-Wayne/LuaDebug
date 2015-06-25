// LuaDebug.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

extern "C" {
#include "lua_debug.h"
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("test lua debug!\n");

	lua_State *L = lua_open();
	luaL_openlibs(L);
	luaL_dofile(L, "Resources/main.lua");

	ld_init(L);

	ld_printstack(L);
	
	return 0;
}

