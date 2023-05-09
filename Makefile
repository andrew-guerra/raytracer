CFLAGS = -g
CC = g++ $(CFLAGS)
SHELL = /bin/bash

.PHONY: all clean

all: raytracing

raytracing: src/raycasting.cpp src/PPMGenerator.cpp src/vectors.cpp
	$(CC) -o $@ $^

run: raytracing
	./raytracing $(sceneFile)

clean:
	rm -f raytracing

help:
	@echo 'Usage:'
	@echo '  > make                          # build program (executable is raytracing)'
	@echo '  > make run sceneFile=FILEPATH   # run program with FILEPATH scene descriptor file'
	@echo '  > make clean                    # remove all compiled items'
