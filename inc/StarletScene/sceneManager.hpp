#pragma once

#include "scene.hpp"
#include "sceneLoader.hpp"

class SceneManager {
public:
  void setBasePath(const char* path) { basePath = path; }

  inline Scene& getScene() { return scene; }

  bool loadTxtScene(const std::string& path);
  bool saveTxtScene();

private:
  std::string basePath;
  Scene scene;
  SceneLoader loader;
};