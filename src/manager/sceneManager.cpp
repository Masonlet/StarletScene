#include "StarletScene/manager/sceneManager.hpp"
#include "StarletSerializer/utils/log.hpp"

#include"StarletSerializer/parser/sceneParser.hpp"
#include "StarletSerializer/writer/writer.hpp"

namespace Starlet::Scene {
  bool SceneManager::loadTxtScene(const std::string& path) {
    Serializer::debugLog("SceneManager", "loadTxtScene", "Started: " + path);
    Serializer::SceneParser parser;
    if (!parser.parse(scene, (basePath + path).c_str())) return Serializer::error("SceneManager", "loadTxtScene", "Failed to load scene file!");

    scene.setScenePath(basePath + path);
    return Serializer::debugLog("SceneManager", "loadTxtScene", "Finished: " + path);
  }

  bool SceneManager::saveTxtScene() {
    Serializer::debugLog("SceneManager", "saveTxtScene", "Started: " + scene.getScenePath());

    Serializer::Writer w;
    if (!w.writeScene(scene))
      return Serializer::error("SceneManger", "saveTxtScene", "Failed to save scene: " + basePath);

    return Serializer::debugLog("SceneManager", "saveTxtScene", "Finished: " + scene.getScenePath());
  }
}