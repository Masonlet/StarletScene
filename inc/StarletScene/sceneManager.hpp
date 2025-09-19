#pragma once

#include "scene.hpp"
#include "sceneLoader.hpp"

class SceneManager {
public:
  void setBasePath(const char* path) { basePath = path; }

  inline Scene& getScene() { return scene; }
  bool saveTxtScene();
  bool loadTxtScene(const std::string& path);

private:
  Scene scene;

  std::string basePath;
  SceneLoader loader;
};