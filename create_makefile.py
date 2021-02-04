import sys,os

base_file = """
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
"""

print("creating the makefile")

root = "./src"
path = os.path.join(root, "src")

ddd_source_files = []

for path, subdirs, files in os.walk(root):
    if "imgui" not in path:
        for name in files:
            if ".c" in name:
                ddd_source_files.append(os.path.join(path, name))

imgui_folder = "./src/screen/imgui/"
imgui_files = ["imgui.cpp", "imgui_draw.cpp", "imgui_tables.cpp", "imgui_widgets.cpp", "backends/imgui_impl_glfw.cpp", "backends/imgui_impl_opengl3.cpp"]

for f in imgui_files:
    ddd_source_files.append(imgui_folder + f)

final = []

for f in ddd_source_files:
    obj = f.split('/')[-1].split('.')[0]
    final.append((f, obj))

final_text = ""

all_final = " ".join(["$(BIN_FOLDER)/" + o + ".o" for f, o in final])
final_text += base_file + "\n\n\n"
final_text += "all: " + all_final + "\n"
final_text += "\t$(CXX) -o $(EXE) " + " ".join("$(BIN_FOLDER)/" + o + ".o" for f, o in final) + " $(CXXFLAGS) $(LIBS)\n\n"

for f, o in final:
    final_text += "$(BIN_FOLDER)/" + o + ".o" + ": " + f + "\n"
    final_text += "\t$(CXX) $(CXXFLAGS) -c " + f + " -o $(BIN_FOLDER)/" + o + ".o" + "\n\n"


print(final_text)