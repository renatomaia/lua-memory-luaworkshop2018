#!/bin/bash

BASEDIR=/home/maia/Work
LMEMDIR=$BASEDIR/lua/proj/memory/git/src
BENCHDIR=$BASEDIR/cujo/talks/luaworkshop/2018/luamemory/benchmark

for d in $LMEMDIR
do
	LUA_CPATH="$LUA_CPATH;$d/?.so"
done

for d in $LMEMDIR $BENCHDIR
do
	LUA_CPATH="$LUA_CPATH;$d/?.so"
done


env \
	LD_LIBRARY_PATH="$LMEMDIR" \
	LUA_PATH"=$LUA_PATH" \
	LUA_CPATH="$LUA_CPATH" \
	lua test.lua $*
