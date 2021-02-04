CXX   = g++ -std=c++14
DEBUG = -g
LIBS  = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp

IMGUI_DIR = src/screen/imgui
CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += -g -Wall -Wformat

BIN_FOLDER=bin
EXE=ddd

LIBS += -lGL `pkg-config --static --libs glfw3`
CXXFLAGS += `pkg-config --cflags glfw3`
CFLAGS = $(CXXFLAGS)



all: $(BIN_FOLDER)/ddd.o $(BIN_FOLDER)/shader.o $(BIN_FOLDER)/glad.o $(BIN_FOLDER)/texture.o $(BIN_FOLDER)/color.o $(BIN_FOLDER)/gobject.o $(BIN_FOLDER)/model.o $(BIN_FOLDER)/mesh.o $(BIN_FOLDER)/inputs.o $(BIN_FOLDER)/camera.o $(BIN_FOLDER)/screen.o $(BIN_FOLDER)/imgui.o $(BIN_FOLDER)/imgui_draw.o $(BIN_FOLDER)/imgui_tables.o $(BIN_FOLDER)/imgui_widgets.o $(BIN_FOLDER)/imgui_impl_glfw.o $(BIN_FOLDER)/imgui_impl_opengl3.o
	$(CXX) -o $(EXE) $(BIN_FOLDER)/ddd.o $(BIN_FOLDER)/shader.o $(BIN_FOLDER)/glad.o $(BIN_FOLDER)/texture.o $(BIN_FOLDER)/color.o $(BIN_FOLDER)/gobject.o $(BIN_FOLDER)/model.o $(BIN_FOLDER)/mesh.o $(BIN_FOLDER)/inputs.o $(BIN_FOLDER)/camera.o $(BIN_FOLDER)/screen.o $(BIN_FOLDER)/imgui.o $(BIN_FOLDER)/imgui_draw.o $(BIN_FOLDER)/imgui_tables.o $(BIN_FOLDER)/imgui_widgets.o $(BIN_FOLDER)/imgui_impl_glfw.o $(BIN_FOLDER)/imgui_impl_opengl3.o $(CXXFLAGS) $(LIBS)

$(BIN_FOLDER)/ddd.o: ./src/ddd.cpp
	$(CXX) $(CXXFLAGS) -c ./src/ddd.cpp -o $(BIN_FOLDER)/ddd.o

$(BIN_FOLDER)/shader.o: ./src/shader/shader.cpp
	$(CXX) $(CXXFLAGS) -c ./src/shader/shader.cpp -o $(BIN_FOLDER)/shader.o

$(BIN_FOLDER)/glad.o: ./src/glad/glad.c
	$(CXX) $(CXXFLAGS) -c ./src/glad/glad.c -o $(BIN_FOLDER)/glad.o

$(BIN_FOLDER)/texture.o: ./src/types/texture.cpp
	$(CXX) $(CXXFLAGS) -c ./src/types/texture.cpp -o $(BIN_FOLDER)/texture.o

$(BIN_FOLDER)/color.o: ./src/types/color.cpp
	$(CXX) $(CXXFLAGS) -c ./src/types/color.cpp -o $(BIN_FOLDER)/color.o

$(BIN_FOLDER)/gobject.o: ./src/gobject/gobject.cpp
	$(CXX) $(CXXFLAGS) -c ./src/gobject/gobject.cpp -o $(BIN_FOLDER)/gobject.o

$(BIN_FOLDER)/model.o: ./src/model/model.cpp
	$(CXX) $(CXXFLAGS) -c ./src/model/model.cpp -o $(BIN_FOLDER)/model.o

$(BIN_FOLDER)/mesh.o: ./src/model/mesh.cpp
	$(CXX) $(CXXFLAGS) -c ./src/model/mesh.cpp -o $(BIN_FOLDER)/mesh.o

$(BIN_FOLDER)/inputs.o: ./src/inputs/inputs.cpp
	$(CXX) $(CXXFLAGS) -c ./src/inputs/inputs.cpp -o $(BIN_FOLDER)/inputs.o

$(BIN_FOLDER)/camera.o: ./src/screen/camera.cpp
	$(CXX) $(CXXFLAGS) -c ./src/screen/camera.cpp -o $(BIN_FOLDER)/camera.o

$(BIN_FOLDER)/screen.o: ./src/screen/screen.cpp
	$(CXX) $(CXXFLAGS) -c ./src/screen/screen.cpp -o $(BIN_FOLDER)/screen.o

$(BIN_FOLDER)/imgui.o: ./src/screen/imgui/imgui.cpp
	$(CXX) $(CXXFLAGS) -c ./src/screen/imgui/imgui.cpp -o $(BIN_FOLDER)/imgui.o

$(BIN_FOLDER)/imgui_draw.o: ./src/screen/imgui/imgui_draw.cpp
	$(CXX) $(CXXFLAGS) -c ./src/screen/imgui/imgui_draw.cpp -o $(BIN_FOLDER)/imgui_draw.o

$(BIN_FOLDER)/imgui_tables.o: ./src/screen/imgui/imgui_tables.cpp
	$(CXX) $(CXXFLAGS) -c ./src/screen/imgui/imgui_tables.cpp -o $(BIN_FOLDER)/imgui_tables.o

$(BIN_FOLDER)/imgui_widgets.o: ./src/screen/imgui/imgui_widgets.cpp
	$(CXX) $(CXXFLAGS) -c ./src/screen/imgui/imgui_widgets.cpp -o $(BIN_FOLDER)/imgui_widgets.o

$(BIN_FOLDER)/imgui_impl_glfw.o: ./src/screen/imgui/backends/imgui_impl_glfw.cpp
	$(CXX) $(CXXFLAGS) -c ./src/screen/imgui/backends/imgui_impl_glfw.cpp -o $(BIN_FOLDER)/imgui_impl_glfw.o

$(BIN_FOLDER)/imgui_impl_opengl3.o: ./src/screen/imgui/backends/imgui_impl_opengl3.cpp
	$(CXX) $(CXXFLAGS) -c ./src/screen/imgui/backends/imgui_impl_opengl3.cpp -o $(BIN_FOLDER)/imgui_impl_opengl3.o
