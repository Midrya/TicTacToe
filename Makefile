objects = main.o minimax.o draw.o
CC = g++
CCFLAGS = -Wall -Wextra -c
LFLAGS = -Wall -Wextra -g
CURSES = -lncurses

ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CCFLAGS += -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CCFLAGS += -D AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CCFLAGS += -D IA32
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D OSX
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CCFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CCFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CCFLAGS += -D ARM
    endif
endif

tictactoe: $(objects)
	$(CC) $(LFGLAGS) $(objects) $(CURSES) -o $@

main.o: main.cpp minimax.hpp draw.hpp
	$(CC) $(CCFLAGS) $< -o $@
minimax.o: minimax.cpp minimax.hpp
	$(CC) $(CCFLAGS) $< -o $@
draw.o: draw.cpp draw.hpp
	$(CC) $(CCFLAGS) $(CURSES) $< -o $@

clean:
	-rm tictactoe *.o
