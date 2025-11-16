CXX = clang++
CXXFLAGS = -std=c++11 -Wall -MMD -MP

SRC_DIR = src
BUILD_DIR = build
TARGET = app

SDL_FLAGS := $(shell sdl2-config --cflags)
SDL_LIBS = $(shell sdl2-config --libs ) -lSDL2_image -lSDL2_ttf -lSDL2_mixer

SRC = $(shell find ${SRC_DIR} -name '*.cpp')
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJ:.o=.d)


PCH_EXT = pch
PCH = $(BUILD_DIR)/pch.h.pch
PCH_SRC = $(SRC_DIR)/pch.h

TARGET = app


all: $(TARGET)


$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(SDL_FLAGS) $(SDL_LIBS)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) -include $(SRC_DIR)/pch.h -c $< -o $@


$(PCH) : $(PCH_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) -x c++-header $< -o $@


-include $(DEPS)

.PHONY: build
build: all

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
