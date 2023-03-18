# CSCI 4061 Lab Makefile
AN=hw1b.andrew.guerra

CFLAGS = -g
CC = g++ $(CFLAGS)
SHELL = /bin/bash
CWD = $(shell pwd | sed 's/.*\///g')

.PHONY: all clean

all: raycasting1c

raycasting1c: raycasting.cpp PPMGenerator.cpp vectors.cpp
	$(CC) -o $@ $^

clean:
	rm -f raycasting1c

help:
	@echo 'Typical usage is:'
	@echo '  > make                          # build all program (executable is raycasting
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'

# 'make zip' to create zip file for submission
zip: clean
	rm -f $(AN).zip
	cd .. && zip "$(CWD)/$(AN).zip" -r "$(CWD)"
	@echo Zip created in $(AN).zip
	@if (( $$(stat -c '%s' $(AN).zip) > 10*(2**20) )); then echo "WARNING: $(AN).zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN).zip | wc -l) > 256 )); then echo "WARNING: $(AN).zip has 256 or more files in it which may cause submission problems"; fi


