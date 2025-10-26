#pragma once

#include "StarletScene/scene.hpp"

namespace Starlet::Scene {
  class SceneManager {
  public:
    void setBasePath(const char* path) { basePath = path; }

    inline Scene& getScene() { return scene; }

    bool loadTxtScene(const std::string& path);
    bool saveTxtScene();

  private:
    std::string basePath;
    Scene scene;
  };
}