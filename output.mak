#Makefile to build a target
CC = gcc
BASEDIR = .
#CFLAGS  = -Wall -I.
# -g for debugging with gdb
#CFLAGS  = -Wall -I. -g
# -O2 optimize for better performance
SDL_CFLAGS := $(shell sdl-config --cflags)
#SDL_LDFLAGS := -lSGE $(shell sdl-config --libs) -lSDL_ttf -lstdc++
SDL_LDFLAGS := $(shell sdl-config --libs) -lSDL_ttf -lstdc++
DEFINES = -DTEST -DTEST_OUTPUT
CFLAGS = -Wall -I. -g -O2 ${SDL_CFLAGS} ${DEFINES}

TARGET = output

SRCS = output.cpp

OBJS = ${SRCS:.cpp=.o} ${SRCS:.c=.o}

all: ${TARGET}

${TARGET}: ${OBJS}
	${CC} ${SDL_LDFLAGS) -o $@ ${OBJS} 

.c.o:
	${CC} -c ${CFLAGS} $*.c

.cpp.o:
	${CC} -c ${CFLAGS} $*.cpp
	
clean:
	rm -rf core ${OBJS} ${TARGET} *.bak
