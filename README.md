# StarletScene
A lightweight scene &amp; scene management library for Starlet projects designed with OpenGL engines in mind.

## Features
- **Scene Objects** : `Camera`, `Model`, `Light`, `Grid`, `Texture`, `TextureConnection`, `Primitive`
- **Scene Containers** 
    - `Scene` :  holds maps of Cameras, Models, Lights, Grids, Textures, TextureConnections, Primitives
    - Helpers : `addObject<T>`, `getObjects<T>`, `getObjectByName`, `getObjectByIndex`, `getObjectCount<T>`
- **Scene I/O**
    - `SceneLoader` : `loadScene` & `saveScene`
    - Human-readable format with tokens: 
        `camera`, `model`, `light`, 
        `texture`, `textureCube`, `textureAdd`
        `triangle`, `square`, `cube`,
        `squareGrid`, `cubeGrid`
        `#` or `comment` for comments

## Using as a Dependency
```cmake
include(FetchContent)

FetchContent_Declare(StarletScene GIT_REPOSITORY https://github.com/Masonlet/StarletScene.git GIT_TAG main)
FetchContent_MakeAvailable(StarletScene)

target_link_libraries(YourAppName PRIVATE StarletScene)
```
