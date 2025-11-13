SDL_FLAGS := $(shell sdl2-config --cflags --libs)

build:
	g++ -std=c++11 -o app \
	main.cpp \
	src/window.cpp \
	src/sdl_utils.cpp \
	src/startup_funcs.cpp \
	src/texture_manager.cpp \
	src/texture.cpp \
	src/cameras/camera.cpp \
	src/cameras/zone_camera.cpp \
	src/ecs/entity.cpp \
	src/ecs/components/sprite.cpp \
	src/ecs/components/position.cpp \
	${SDL_FLAGS} -lSDL2_image -lSDL2_ttf -lSDL2_mixer
