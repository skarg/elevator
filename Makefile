#Makefile to build a target
CC      = gcc
BASEDIR = .
#CFLAGS  = -Wall -I.
# -g for debugging with gdb
#CFLAGS  = -Wall -I. -g 
# -O2 optimize for better performance

# sudo apt-get install libsdl2-dev
# sudo apt-get install libsdl2-ttf-dev 
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs) -lSDL_ttf -lstdc++
CFLAGS  = -Wall -Wno-deprecated -I. -g -O2 ${SDL_CFLAGS}

TARGET = elevator

SRCS = display.cpp elevator.cpp elevsim.cpp \
	elevsupp.cpp elevtask.cpp output.cpp graphics.cpp \
	passnger.cpp poisson.cpp report.cpp

OBJS = ${SRCS:.cpp=.o}

all: ${TARGET}

${TARGET}: ${OBJS}
	${CC} -o $@ ${OBJS} ${SDL_LDFLAGS}

.cpp.o:
	${CC} -c ${CFLAGS} $*.cpp
	
depend:
	rm -f .depend
	${CC} -MM ${CFLAGS} *.cpp >> .depend
	
clean:
	rm -rf core ${OBJS} ${TARGET} *.bak *~

include: .depend
