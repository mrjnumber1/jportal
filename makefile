SHELL = /bin/sh/

.SUFFIXES:
.SUFFIXES: .c .o

BASEDIR = .
SRCDIR = $(BASEDIR)/src
INCDIR = $(BASEDIR)/include
INCLUDES = 
C_FILES = $(wildcard $(SRCDIR)/*.c)
OBJ_FILES = $(addprefix obj/,$(notdir $(C_FILES:.c=.o))) 
CC = gcc
SDL_CFLAGS = -I/opt/windows_32/include/SDL2 -Dmain=SDL_main
SDL_LDFLAGS = -L/opt/windows_32/lib -lmingw32 -lSDL2main -lSDL2 -mwindows 
CFLAGS = $(INCLUDES) -g -pedantic -Wall -Werror -Wfatal-errors --std=gnu11 $(SDL_CFLAGS)
LDFLAGS = $(SDL_LDFLAGS)
MAIN = rungame.exe

all: $(MAIN)
	@echo Compiling rungame... 

$(MAIN): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	$(RM) $(OBJ_FILES) 
	$(RM) ./*~
	$(RM) ./include/*~
	$(RM) ./src/*~
	$(RM) $(MAIN)



