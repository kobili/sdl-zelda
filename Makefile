SDL_FLAGS := $(shell sdl2-config --cflags --libs)

build:
	g++ -std=c++11 -o app \
	main.cpp \
	src/window.cpp \
	src/sdl_utils.cpp \
	src/startup_funcs.cpp \
	src/texture_manager.cpp \
	src/texture.cpp \
	${SDL_FLAGS} -lSDL2_image -lSDL2_ttf -lSDL2_mixer
