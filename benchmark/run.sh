#!/bin/bash

BASEDIR=/home/maia/Work
LMEMDIR=$BASEDIR/lua/proj/memory/git/src
LBENCHSRC=$BASEDIR/lua/proj/bench/git/src
BENCHDIR=$BASEDIR/cujo/talks/luaworkshop/2018/luamemory/benchmark

#LUA_PATH:=';'
for d in \
	$BASEDIR/lua/proj/loop/modules/git/lua \
	$LBENCHSRC
do
	LUA_PATH="$LUA_PATH;$d/?.lua"
done

#LUA_CPATH:=';'
for d in \
	$LMEMDIR \
	$BENCHDIR
do
	LUA_CPATH="$LUA_CPATH;$d/?.so"
done

rm $BENCHDIR/*.csv

for (( i = 1; i <= $1; i++ ))
do
	echo "Execution $i/$1"
	env \
		LD_LIBRARY_PATH="$LMEMDIR" \
		LUA_PATH"=$LUA_PATH" \
		LUA_CPATH="$LUA_CPATH" \
		lua $LBENCHSRC/run.lua $BENCHDIR
done

env \
	LUA_PATH"=$LUA_PATH" \
	lua $LBENCHSRC/plot.lua gnuplot $BENCHDIR/*.csv
