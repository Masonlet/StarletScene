#include "StarletScene/sceneManager.hpp"

#include "StarletParser/parser.hpp"
#include "StarletParser/writer.hpp"
#include "StarletParser/utils/log.hpp"

bool SceneManager::loadTxtScene(const std::string& path) {
  debugLog("SceneManager", "loadTxtScene", "Started: " + path);
  Parser parser;
  if (!parser.parseScene(scene, (basePath + path).c_str())) return error("SceneManager", "loadTxtScene", "Failed to load scene file!");

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