VERSION=-std=c++14
COMP=g++
FLAGS=-Wall -Wextra
LIBS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
BIN_FOLDER=bin
EXEC=ddd

all: src/glad/glad.c src/shader/shader.cpp src/types/color.cpp src/screen/screen.cpp src/inputs/inputs.cpp src/ddd.cpp
	$(COMP) $^ $(VERSION) $(FLAGS) $(LIBS) -o $(BIN_FOLDER)/$(EXEC) 
