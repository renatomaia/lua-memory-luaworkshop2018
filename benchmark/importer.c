#define importer_c

#include "lmemlib.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#if !defined(l_rand)            /* { */
#if defined(LUA_USE_POSIX)
#define l_rand()        random()
#define l_srand(x)      srandom(x)
#define L_RANDMAX       2147483647      /* (2^31 - 1), following POSIX */
#else
#define l_rand()        rand()
#define l_srand(x)      srand(x)
#define L_RANDMAX       RAND_MAX
#endif
#endif                          /* } */

#define METANAME "BinImport"
#define MAXVALUE 0xff

static void nextvalue(char *mem, size_t size) {
	unsigned char *memory = (unsigned char *)mem;
	for (int i = 0; i < size; ++i) {
		if (memory[i] < MAXVALUE-1) {
			++(memory[i]);
			break;
		}
		memory[i] = 0x00;
	}
}

static int imp_skip (lua_State *L) {
	char *buf = luaL_checkudata(L, 1, METANAME);;
	size_t bufsz = lua_rawlen(L, 1);
	lua_settop(L, 1);
	nextvalue(buf, bufsz);
	lua_pushboolean(L, 1);
	return 1;
}

static int imp_setref (lua_State *L) {
	char *buf = luaL_checkudata(L, 1, METANAME);;
	size_t bufsz = lua_rawlen(L, 1);
	lua_settop(L, 2);
	nextvalue(buf, bufsz);
	return luamem_setref(L, 2, buf, bufsz, NULL);
}

static int imp_newref (lua_State *L) {
	char *buf = luaL_checkudata(L, 1, METANAME);;
	size_t bufsz = lua_rawlen(L, 1);
	lua_settop(L, 1);
	nextvalue(buf, bufsz);
	luamem_newref(L);
	luamem_setref(L, -1, buf, bufsz, NULL);
	return 1;
}

static int imp_setmem (lua_State *L) {
	char *buf = luaL_checkudata(L, 1, METANAME);;
	size_t bufsz = lua_rawlen(L, 1);
	size_t sz;
	char *p = luamem_tomemory(L, 2, &sz);
	if (sz != bufsz) return 0;
	lua_settop(L, 2);
	nextvalue(buf, bufsz);
	memcpy(p, buf, bufsz);
	return 1;
}

static int imp_newmem (lua_State *L) {
	char *buf = luaL_checkudata(L, 1, METANAME);;
	size_t bufsz = lua_rawlen(L, 1);
	char *p;
	lua_settop(L, 1);
	nextvalue(buf, bufsz);
	p = luamem_newalloc(L, bufsz);
	memcpy(p, buf, bufsz);
	return 1;
}

static int imp_string (lua_State *L) {
	char *buf = luaL_checkudata(L, 1, METANAME);;
	size_t bufsz = lua_rawlen(L, 1);
	lua_settop(L, 1);
	nextvalue(buf, bufsz);
	lua_pushlstring(L, buf, bufsz);
	return 1;
}

static int imp_create (lua_State *L) {
	size_t bufsz = luamem_checklenarg(L, 1);
	char *buf = lua_newuserdata(L, bufsz);
	srand((int)time(NULL));
	memset(buf, rand()%MAXVALUE, bufsz);
	luaL_setmetatable(L, METANAME);
	return 1;
}

static const luaL_Reg lib[] = {
	{"create", imp_create},
	{NULL, NULL}
};

static const luaL_Reg meta[] = {
	{"skip"  , imp_skip  },
	{"setref", imp_setref},
	{"newref", imp_newref},
	{"setmem", imp_setmem},
	{"newmem", imp_newmem},
	{"string", imp_string},
	{NULL, NULL}
};


static void setupmetatable (lua_State *L, const char *name) {
	luaL_newmetatable(L, name);
	luaL_setfuncs(L, meta, 0);  /* add metamethods to new metatable */
	lua_pushvalue(L, -1);  /* push library */
	lua_setfield(L, -2, "__index");  /* metatable.__index = library */
	lua_pop(L, 1);  /* pop new metatable */
}


int luaopen_importer (lua_State *L) {
	luaL_newlib(L, lib);
	setupmetatable(L, METANAME);
	return 1;
}
