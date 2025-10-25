#include "StarletScene/manager/sceneManager.hpp"
#include "StarletSerializer/utils/log.hpp"

#include"StarletSerializer/parser/sceneParser.hpp"
#include "StarletSerializer/writer/writer.hpp"

bool SceneManager::loadTxtScene(const std::string& path) {
  debugLog("SceneManager", "loadTxtScene", "Started: " + path);
  SceneParser parser;
  if (!parser.parse(scene, (basePath + path).c_str())) return error("SceneManager", "loadTxtScene", "Failed to load scene file!");

  scene.setScenePath(basePath + path);
  return debugLog("SceneManager", "loadTxtScene", "Finished: " + path);
}

bool SceneManager::saveTxtScene() {
  debugLog("SceneManager", "saveTxtScene", "Started: " + scene.getScenePath());
 
  Writer w;
  if (!w.writeScene(scene))
    return error("SceneManger", "saveTxtScene", "Failed to save scene: " + basePath);

  return debugLog("SceneManager", "saveTxtScene", "Finished: " + scene.getScenePath());
}