CFLAGS = -g
CC = g++ $(CFLAGS)
SHELL = /bin/bash

.PHONY: all clean

all: math image render raytracer-renderer

math: build
	cd libs/math; make

image: build math
	cd libs/image; make

render: build math image
	cd libs/render; make

raytracer-renderer: build math image render
	cd apps/raytracer-renderer; make

build:
	mkdir -p build

run: build
	./build/bin/raytracer-renderer $(sceneFile)

docs:
	cd docs; doxygen Doxyfile

clean:
	rm -rf build

clean-docs:
	rm -rf docs/html
	rm -rf docs/latex

help:
	@echo 'Usage:'
	@echo '  > make                          # build program (executable is raytracing)'
	@echo '  > make run sceneFile=FILEPATH   # run program with FILEPATH scene descriptor file'
	@echo '  > make clean                    # remove all compiled items'
