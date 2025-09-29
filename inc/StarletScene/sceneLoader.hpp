#pragma once

struct Scene;

class SceneLoader {
public:
	bool loadScene(Scene& scene, const std::string& path);
	bool saveScene(const Scene& scene);
};