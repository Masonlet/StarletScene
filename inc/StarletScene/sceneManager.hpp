#pragma once

#include "scene.hpp"
#include "sceneLoader.hpp"

struct SceneManager {
  Scene scene;

  bool saveTxtScene();
  bool loadTxtScene(const std::string& path);

private:
  SceneLoader loader;
};