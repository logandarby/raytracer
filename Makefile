# Makefile modified from https://www.partow.net/programming/makefile/index.html

CXX      := g++
CXXFLAGS := -std=c++20 -pedantic-errors -Wall -Wextra -Werror=vla 
LDFLAGS  := -L dependencies/lib -lmingw32 -lSDL2main -lSDL2 -lgdi32 -lopengl32 -limm32 
INCLUDE  := -I dependencies/include/ImGUI -I dependencies/include/ImGUI/backends -I dependencies/include/SDL2 -I ./src
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := .
EXEC     := program
SRC      := \
	$(wildcard src/*.cpp) \
	$(wildcard src/common/*.cpp) \
	$(wildcard src/util/*.cpp) \
	$(wildcard src/engine/*.cpp) \
	$(wildcard src/engine/BVH/*.cpp) \
	$(wildcard dependencies/include/ImGUI/*.cpp) \

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDS=${OBJECTS:.o=.d}

all: build $(APP_DIR)/$(EXEC)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(EXEC): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(OBJECTS)  $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(EXEC)  

-include ${DEPENDS}

.PHONY: clean

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -vf $(APP_DIR)/$(EXEC).exe

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

profile: CXXFLAGS += -pg -O0
profile: all

release: CXXFLAGS += -O3
release: all

info:
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"
