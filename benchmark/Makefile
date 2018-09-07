# == CHANGE THE SETTINGS BELOW TO SUIT YOUR ENVIRONMENT =======================

LUA_HOME= /home/maia/Work/lua/build/5.3
LUA_INC= $(LUA_HOME)/include
LUA_LIB= $(LUA_HOME)/lib
LUA_BIN= $(LUA_HOME)/bin

LMEM_HOME= /home/maia/Work/lua/proj/memory/git
LMEM_INC= $(LMEM_HOME)/src
LMEM_LIB= $(LMEM_HOME)/src

# Your platform. See PLATS for possible values.
PLAT= none

CC= gcc -std=gnu99
CFLAGS= -O2 -Wall -I$(LUA_INC) -I$(LMEM_INC) $(SYSCFLAGS) $(MYCFLAGS)
LDFLAGS= -L$(LMEM_LIB) $(SYSLDFLAGS) $(MYLDFLAGS)
LIBS= -lluamemlib $(SYSLIBS) $(MYLIBS)

AR= ar rcu
RANLIB= ranlib
RM= rm -f

SYSCFLAGS=
SYSLDFLAGS=
SYSLIBS=

MYCFLAGS=
MYLDFLAGS=
MYLIBS=

# == END OF USER SETTINGS -- NO NEED TO CHANGE ANYTHING BELOW THIS LINE =======

PLATS= linux macosx

OBJ=	importer.o

MOD=	importer.so

TGR= $(MOD)

default: $(PLAT)

all:	$(TGR)

o:	$(OBJ)

m:	$(MOD)

$(MOD): $(OBJ)
	$(LD) -o $@ $(LDFLAGS) $^ $(LIBS)

clean:
	$(RM) $(TGR) $(OBJ)

depend:
	@$(CC) $(CFLAGS) -MM l*.c

echo:
	@echo "PLAT= $(PLAT)"
	@echo "CC= $(CC)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(SYSLDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "AR= $(AR)"
	@echo "RANLIB= $(RANLIB)"
	@echo "RM= $(RM)"

# Convenience targets for usual platforms
ALL= all

none:
	@echo "Please do 'make PLATFORM' where PLATFORM is one of these:"
	@echo "   $(PLATS)"

linux:
	$(MAKE) $(ALL) LD="gcc" MYCFLAGS="-fpic $(MYCFLAGS)" \
	               MYLDFLAGS="-Wl,-E -O -shared $(MYLDFLAGS)"

macosx:
	$(MAKE) $(ALL) MYCFLAGS="-fno-common $(MYCFLAGS)" \
	               MYLDFLAGS="-bundle -undefined dynamic_lookup $(MYLDFLAGS)" \
	               LD='export MACOSX_DEPLOYMENT_TARGET="10.10"; gcc'

# (end of Makefile)
