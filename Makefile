CFLAGS = -g
CC = g++ $(CFLAGS)
SHELL = /bin/bash
CWD = $(shell pwd | sed 's/.*\///g')

.PHONY: all clean

all: raycasting

raycasting: raycasting.cpp PPMGenerator.cpp vectors.cpp
	$(CC) -o $@ $^

clean:
	rm -f raycasting

help:
	@echo 'Typical usage is:'
	@echo '  > make                          # build all program (executable is raycasting
	@echo '  > make clean                    # remove all compiled items'

