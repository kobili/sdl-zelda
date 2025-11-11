SDL_FLAGS := $(shell sdl2-config --cflags --libs)

build:
	g++ -std=c++11 -o app \
		main.cpp \
		src/window.cpp \
		src/texture.cpp \
		src/sprite_sheet.cpp \
		src/sdl_utils.cpp \
		src/player.cpp \
		src/entity.cpp \
		src/utils.cpp \
		src/observer.cpp \
		${SDL_FLAGS} -lSDL2_image -lSDL2_ttf -lSDL2_mixer
