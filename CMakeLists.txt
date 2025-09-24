cmake_minimum_required(VERSION 3.20)

set(SCENE_NAME StarletScene)
set(SCENE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SCENE_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc")

if(NOT TARGET ${SCENE_NAME})
  add_library(${SCENE_NAME} STATIC)

  file(GLOB_RECURSE SCENE_SRC CONFIGURE_DEPENDS ${SCENE_SRC_DIR}/*.cpp)
  file(GLOB_RECURSE SCENE_HEADERS CONFIGURE_DEPENDS ${SCENE_INC_DIR}/StarletScene/*.hpp)

  source_group(TREE ${SCENE_SRC_DIR} PREFIX "Source Files" FILES ${SCENE_SRC})
  source_group(TREE ${SCENE_INC_DIR} PREFIX "Header Files" FILES ${SCENE_HEADERS})

  target_sources(${SCENE_NAME} PRIVATE ${SCENE_SRC} ${SCENE_HEADERS})
  target_include_directories(${SCENE_NAME} PUBLIC $<BUILD_INTERFACE:${SCENE_INC_DIR}> $<INSTALL_INTERFACE:include>)
  target_link_libraries(${SCENE_NAME} PUBLIC StarletParsers StarletControls)
endif()
