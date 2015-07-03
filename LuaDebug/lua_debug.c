#include "lua_debug.h"

#define LDLOG(var) do { printf("*** [LueDebug] *** :"); printf((var)); printf("\n"); } while (0)

ld_Info *ld_new(lua_State *L)
{
    if (!L) {
        return NULL;
    }
    
    ld_Info *ldInfo = (ld_Info *)malloc(sizeof(ld_Info));
    memset(ldInfo, 0, sizeof(ld_Info));
    
    ldInfo->L = L;

	printf("TValue size : %lu\n", sizeof(TValue));
	printf("Value size : %lu\n", sizeof(Value));
	printf("StkId size : %lu\n", sizeof(StkId));
	printf("TString size : %lu\n", sizeof(TString));
	// printf("TString::tsv size : %d\n", sizeof(TString::tsv));
	// printf("TString::dummy size : %d\n", sizeof(TString::dummy));
    
    // luaL_openlibs(L);
    // lua_pushcfunction(L, ld_register);
    // lua_register(L, n, f) // removed from 5.2
    const luaL_Reg ld_cfuncs[] =
    {
        {"ld_printstack", ld_register},
        {NULL, NULL}
    };
    luaL_register(L, "_G", ld_cfuncs);
    
    return ldInfo;
}

void ld_printstack(lua_State *L)
{
	StkId top = L->top;
	StkId base = L->base;
	StkId stack =L->stack;

	StkId curr = top--;
	int stackCount = (int)(top - stack);

    printf("\n================================================ \n");
	printf("===== stack size :%d\n", stackCount);

	while (stackCount > 0)
	{
        
		Value value =  curr->value;
		int type = curr->tt;
		switch (type)
		{
		case LUA_TNIL:
			printf("[%d]\t nil \n", stackCount);
			break;
		case LUA_TBOOLEAN:
			printf("[%d]\t bool \t%s\n", stackCount, l_isfalse(curr) ? "false" : "true");
			break;
		case LUA_TLIGHTUSERDATA:
			printf("[%d]\t dataptr \t%p\n", stackCount, value.p);
			break;
		case LUA_TNUMBER:
			printf("[%d]\t number \t%f\n", stackCount, value.n);
			break;
		case LUA_TSTRING:
			printf("[%d]\t string \t%s\n", stackCount, &(value.gc->ts) + 1);
			break;
		case LUA_TTABLE:
			printf("[%d]\t table \t\n", stackCount);
			break;
		case LUA_TFUNCTION:
            {
                Closure clouse = value.gc->cl;
                if (clouse.c.isC) {
                    printf("[%d]\t cfunction \t%010p\n", stackCount, clouse.c.f);
                } else {
                    printf("[%d]\t lfunction \t%s\n", stackCount, clouse.l.p->source + 1);
                    Instruction *currCode = clouse.l.p->code;
                    for (int i=0; i<clouse.l.p->sizecode; i++) {
                        OpCode opCode = GET_OPCODE(*currCode);
                        printf("\t\t%u\t%s\n", opCode, luaP_opnames[opCode]);
                        currCode++;
                    }
                }
            }
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
		stackCount--;
	}
    
    printf("================================================ \n");
}

int ld_register(lua_State *L)
{
    ld_printstack(L);
    return 0;
}