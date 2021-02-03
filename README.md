# DDD
a very simple 3D game engine, wrote to learn game engine programming !

## folders
the project is structured as :
```
/assets          all the assets of used in the engine
/bin             the folder where Makefile puts the binaries
/include         all the .hpp files
/lib             libraries used in the engine (glm, assimp)
/shaders         all the shaders used in the engine
/src/glad        the GLAD api (glad.c)
/src/gobject     DDD's Game Object (abstraction of an object in the engine)
/src/inputs      control all the engine inputs
/src/models      used for model handling
/src/screen      window and rendering stuff
/src/shader      shader handling stuff
/src/types       all basic types
```

## install
 - install all the 3D stuff
```sudo apt-get install libsoil-dev libglm-dev libassimp-dev libglew-dev libglfw3-dev libxinerama-dev libxcursor-dev libxi-dev```
 - install assimp (model loader)
   - download the source on their website
   - build it and install it

## licence
dont hide the engine name pls

