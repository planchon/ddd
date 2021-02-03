VERSION=-std=c++14
COMP=g++
FLAGS=-Wall -Wextra
LIBS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
MY_LIB=-L include/
BIN_FOLDER=bin
EXEC=ddd

all: src/glad/glad.c src/types/texture.cpp src/shader/shader.cpp src/types/color.cpp src/screen/camera.cpp src/screen/screen.cpp src/inputs/inputs.cpp src/ddd.cpp
	$(COMP) $^ $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -o $(BIN_FOLDER)/$(EXEC) 
