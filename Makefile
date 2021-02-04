# VERSION=-std=c++14
# COMP=g++ -g 
# FLAGS=-Wall -Wextra
# LIBS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp
# MY_LIB=-L include/

CXX   = g++ -std=c++14
DEBUG = -g
LIBS  = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp

IMGUI_DIR = src/screen/imgui
CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += -g -Wall -Wformat

SOURCES  = src/ddd.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SOURCES += src/glad/glad.c
SOURCES += src/types/texture.cpp src/types/color.cpp
SOURCES += src/shader/shader.cpp
SOURCES += src/model/mesh.cpp src/model/model.cpp
SOURCES += src/screen/camera.cpp src/screen/screen.cpp
SOURCES += src/inputs/inputs.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

BIN_FOLDER=bin
EXE=ddd

LIBS += -lGL `pkg-config --static --libs glfw3`
CXXFLAGS += `pkg-config --cflags glfw3`
CFLAGS = $(CXXFLAGS)

all: comp
	$(CXX) -o test $(OBJS) $(CXXFLAGS) $(LIBS)

comp:
	$(CXX) $(CXXFLAGS) -c $(SOURCES)

# all: $(EXE)
# 	@echo Build complete

# $(EXE): $(OBJS)
# 	$(CXX) -o $(BIN_FOLDER)/$@ $(BIN_FOLDER)/$^ $(CXXFLAGS) $(LIBS)





# src/screen/imgui/imgui.cpp src/screen/imgui/imgui_impl_glfw.cpp src/screen/imgui/imgui_impl_opengl3.cpp

# all: glad types shader model screen inputs main
# 	# $(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -o $(EXEC) bin/*.o
# 	g++ bin/*.o -L include/ -Wall -Wextra -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp -o bin/test

# imgui: 
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/screen/imgui/imgui.cpp -o $(BIN_FOLDER)/imgui.o
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/screen/imgui/imgui_impl_glfw.cpp -o $(BIN_FOLDER)/imgui_impl_glfw.o
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/screen/imgui/imgui_impl_opengl3.cpp -o $(BIN_FOLDER)/imgui_impl_opengl3.o

# glad: 
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/glad/glad.c -o $(BIN_FOLDER)/glad.o

# types: 
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/types/texture.cpp -o $(BIN_FOLDER)/texture.o
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/types/color.cpp -o $(BIN_FOLDER)/color.o

# shader: src/shader/shader.cpp
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/shader/shader.cpp -o $(BIN_FOLDER)/shader.o

# model: src/model/mesh.cpp src/model/model.cpp
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/model/mesh.cpp -o $(BIN_FOLDER)/mesh.o
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/model/model.cpp -o $(BIN_FOLDER)/model.o

# screen: src/screen/camera.cpp src/screen/screen.cpp
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/screen/camera.cpp -o $(BIN_FOLDER)/camera.o
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/screen/screen.cpp -o $(BIN_FOLDER)/screen.o

# inputs: src/inputs/inputs.cpp
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/inputs/inputs.cpp -o $(BIN_FOLDER)/inputs.o

# main:
# 	$(COMP) $(VERSION) $(FLAGS) $(MY_LIB) $(LIBS) -c src/ddd.cpp -o $(BIN_FOLDER)/ddd.o
	
