CFLAGS = -g
CC = g++ $(CFLAGS)
SHELL = /bin/bash

.PHONY: all clean

all: raycasting

raycasting: src/raycasting.cpp src/PPMGenerator.cpp src/vectors.cpp
	$(CC) -o $@ $^

clean:
	rm -f raycasting

help:
	@echo 'Typical usage is:'
	@echo '  > make                          # build program (executable is raycasting)
	@echo '  > make clean                    # remove all compiled items'

