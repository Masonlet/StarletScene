# Starlet Scene
A lightweight ECS-based scene &amp; scene management library for Starlet projects designed with OpenGL engines in mind.

## Features
- **Entity-Component System (ECS)**
    - `Scene` : manages **entities**, each of which can hold multiple components.
    - Core components:
        - `Camera`, `Model`, `Light`, `Grid`, `TextureData`, `TextureConnection`, `Primitive`, `TransformComponent`, `VelocityComponent`
    - Core systems:
        - `CameraMoveSystem`, `CameraLookSystem`, `CameraFovSystem`, `VelocitySystem`

- **Scene I/O**
    - `SceneLoader` : `loadScene` & `saveScene`
    - Human-readable format with tokens: 
        `camera`, `model`, `light`, 
        `texture`, `textureCube`, `textureAdd`
        `triangle`, `square`, `cube`,
        `squareGrid`, `cubeGrid`,
        `velocity`,
        `#` or `comment` for comments

## Using as a Dependency
```cmake
include(FetchContent)

FetchContent_Declare(starlet_scene
  GIT_REPOSITORY https://github.com/masonlet/starlet-scene.git 
  GIT_TAG main
)
FetchContent_MakeAvailable(starlet_scene)

target_link_libraries(app_name PRIVATE starlet_scene)
```
