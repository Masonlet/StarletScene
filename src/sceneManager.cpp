#include "StarletScene/sceneManager.hpp"

#include "StarletParsers/utils/log.hpp"

bool SceneManager::loadTxtScene(const std::string& path) {
	debugLog("SceneManager", "loadTxtScene", "Started: " + path);
	if (!loader.loadScene(scene, (basePath + path).c_str())) return error("SceneManager", "loadTxtScene", "Failed to load scene file!");
	scene.setScenePath(path);
	return debugLog("SceneManager", "loadTxtScene", "Finished: " + path);
}

bool SceneManager::saveTxtScene() {
	debugLog("SceneManager", "saveTxtScene", "Started: " + scene.getScenePath());
	if (!loader.saveScene(scene)) return error("SceneManager", "saveTxtScene", "Failed to save scene file!");
	return debugLog("SceneManager", "saveTxtScene", "Finished: " + scene.getScenePath());
}