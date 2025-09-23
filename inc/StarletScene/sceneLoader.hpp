#pragma once

struct Scene;

class SceneLoader {
public:
	bool loadScene(Scene& scene, const std::string& path);
	bool saveScene(const Scene& scene);

private:
  bool processSceneLine(Scene& scene, const unsigned char*& p);

  template<typename T>
  bool parseAndAddObject(Scene& scene, const unsigned char*& p, bool (*parseFN)(const unsigned char*&, T&), StarEntity entity) {
    T* component = scene.addComponent<T>(entity);
		return parseFN(p, *component);
  }
};