SDL_FLAGS := $(shell sdl2-config --cflags --libs)

build:
	g++ -std=c++11 -o app \
		main.cpp \
		src/window.cpp \
		src/texture.cpp \
		src/sprite_sheet.cpp \
		src/sdl_utils.cpp \
		src/entities/player.cpp \
		src/entities/entity.cpp \
		src/utils.cpp \
		src/window_observer.cpp \
		src/resource_manager.cpp \
		src/tiles/tileset.cpp \
		src/tiles/tile.cpp \
		src/startup_funcs.cpp \
		src/cameras/camera.cpp \
		src/cameras/zone_camera.cpp \
		src/cameras/panning_camera.cpp \
		${SDL_FLAGS} -lSDL2_image -lSDL2_ttf -lSDL2_mixer
