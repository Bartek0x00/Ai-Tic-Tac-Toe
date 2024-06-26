CC:=gcc
CFLAGS:=-Wall -O3

SRCS:=$(wildcard src/main/*.c) $(wildcard src/AI/*.c) 
DISPLAY_SRCS:=
EXEC:=tictactoe

.PHONY: all clean help tui sdl2 tictactoe

all: help

help: 
	@echo "Usage: make [sdl2|tui|web]"

tui: DISPLAY_SRCS = $(wildcard src/display-tui/*.c)
tui: link

sdl2: DISPLAY_SRCS = $(wildcard src/display-sdl2/*.c)
sdl2: CFLAGS += -lSDL2 -lSDL2_image -lSDL2_ttf
sdl2: link

web: CC = emcc
web: DISPLAY_SRCS = $(wildcard src/display-sdl2/*.c)
web: CFLAGS += -sASYNCIFY=1 -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -sSDL2_IMAGE_FORMATS='["png"]' --shell-file src/display-web/blank.html
web: EXEC = docs/index.html
web: link

link:
	$(CC) $(CFLAGS) -o $(EXEC) $(SRCS) $(DISPLAY_SRCS)
	$(MAKE) clean

clean:
	rm -rf src/*.o
