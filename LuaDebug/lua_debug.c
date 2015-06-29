#include "lua_debug.h"

#define LDLOG(var) do { printf("*** [LueDebug] *** :"); printf((var)); printf("\n"); } while (0)

void ld_init(lua_State *L)
{
	printf("TValue size : %d\n", sizeof(TValue));
	printf("Value size : %d\n", sizeof(Value));
	printf("StkId size : %d\n", sizeof(StkId));
	printf("TString size : %d\n", sizeof(TString));
	// printf("TString::tsv size : %d\n", sizeof(TString::tsv));
	// printf("TString::dummy size : %d\n", sizeof(TString::dummy));
}

void ld_printstack(lua_State *L)
{
	StkId top = L->top;
	StkId base = L->base;
	StkId stack =L->stack;

	StkId curr = top--;
	int stackCount = 1;

	printf("stack size :%d\n", top - stack);

	while (curr >= base)
	{
		Value value =  curr->value;
		int type = curr->tt;
		switch (type)
		{
		case LUA_TNIL:
			printf("[%d]\tLUA_TNIL\n", stackCount);
			break;
		case LUA_TBOOLEAN:
			printf("[%d]\tLUA_TBOOLEAN\t%s\n", stackCount, l_isfalse(curr) ? "false" : "true");
			break;
		case LUA_TLIGHTUSERDATA:
			printf("[%d]\tLUA_TLIGHTUSERDATA\t%p\n", stackCount, value.p);
			break;
		case LUA_TNUMBER:
			printf("[%d]\tLUA_TNUMBER\t%d\n", stackCount, value.n);
			break;
		case LUA_TSTRING:
			printf("[%d]\tLUA_TSTRING\t%s\n", stackCount, (&(value.gc->ts) + 1));
			break;
		case LUA_TTABLE:
			printf("[%d]\tLUA_TTABLE\t\n", stackCount);
			break;
		case LUA_TFUNCTION:
			printf("[%d]\tLUA_TFUNCTION\t\n", stackCount);
			
			break;
		case LUA_TUSERDATA:
			printf("[%d]\tLUA_TUSERDATA\t\n", stackCount);
			break;
		case LUA_TTHREAD:
			printf("[%d]\tLUA_TTHREAD\t\n", stackCount);
			break;
		default:
			printf("[%d]\tLUA_TNONE\t\n", stackCount);
			break;
		}

		curr--;
		stackCount++;
	}
}