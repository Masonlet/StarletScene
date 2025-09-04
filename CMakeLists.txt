cmake_minimum_required(VERSION 3.20)
project(StarletScene)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SUPPRESS_REGENERATION ON)

add_library(StarletScene STATIC)

file(GLOB_RECURSE SCENE_SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE SCENE_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/inc/StarletScene/*.hpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SCENE_SRC})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/inc PREFIX "Header Files" FILES ${SCENE_HEADERS})

target_sources(StarletScene
  PRIVATE ${SCENE_SRC}
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/inc
    FILES ${SCENE_HEADERS}
)

target_include_directories(StarletScene PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
  $<INSTALL_INTERFACE:include>
)

include(FetchContent)
FetchContent_Declare(StarletParsers GIT_REPOSITORY https://github.com/masonlet/starletparsers.git GIT_TAG main)
FetchContent_MakeAvailable(StarletParsers)
target_link_libraries(StarletScene PUBLIC StarletParsers)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "External")
