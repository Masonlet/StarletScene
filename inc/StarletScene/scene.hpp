#pragma once

#include "objects/model.hpp"
#include "objects/light.hpp"
#include "objects/camera.hpp"
#include "objects/grid.hpp"
#include "objects/textureData.hpp"
#include "objects/textureConnection.hpp"
#include "objects/primitive.hpp"
#include "starletparsers/utils/log.hpp"
#include <map>
#include <string>
#include <iterator>

class Scene {
public:
  inline void setScenePath(const std::string& path) { this->path = path; }
  const std::string& getScenePath() const { return path; }

  template<typename T>
  static constexpr const char* typeName() noexcept {
    return typeName(static_cast<T*>(nullptr));
  }

  template <typename T>
  bool addObject(const T& data, const char* type) {
    return addObjectData(getObjects<T>(), data, type);
  }

  template <typename T>
  std::map<std::string, T>& getObjects() { return getObjects(static_cast<T*>(nullptr)); }
  template <typename T>
  const std::map<std::string, T>& getObjects() const { return getObjects(static_cast<T*>(nullptr)); }

  template <typename T>
  bool getObjectByName(const std::string& objName, T*& out) {
    std::map<std::string, T>& map = getObjects<T>();
    typename std::map<std::string, T>::iterator it = map.find(objName);
    if (it == map.end()) return error("Scene", "getObjectByName", std::string(typeName<T>()) + " not found: " + objName);
    out = &it->second;
    return true;
  }

  template <typename T>
  bool getObjectByIndex(size_t index, T*& out) {
    std::map<std::string, T>& map = getObjects<T>();
    if (index >= map.size()) return error("Scene", "getObjectByIndex", std::string(typeName<T>()) + " not found: " + std::to_string(index));
    typename std::map<std::string, T>::iterator it = std::next(map.begin(), index);
		if (it == map.end()) return error("Scene", "getObjectByIndex", std::string(typeName<T>()) + " not found: " + std::to_string(index));
    out = &it->second;
    return true;
  }

  template <typename T>
  size_t getObjectCount() const { return getObjects<T>().size(); }
private:
  std::string path;
  std::map<std::string, Model> models;
  std::map<std::string, Camera> cameras;
  std::map<std::string, Light> lights;
  std::map<std::string, Grid> grids;
  std::map<std::string, TextureData> textures;
  std::map<std::string, TextureConnection> textureConnections;
  std::map<std::string, Primitive> primitives;

  static constexpr const char* typeName(void*) { return "Object"; }
  static constexpr const char* typeName(Model*) { return "Model"; }
  static constexpr const char* typeName(Camera*) { return "Camera"; }
  static constexpr const char* typeName(Light*) { return "Light"; }
  static constexpr const char* typeName(Grid*) { return "Grid"; }
  static constexpr const char* typeName(TextureData*) { return "Texture"; }
  static constexpr const char* typeName(TextureConnection*) { return "TextureConnection"; }
  static constexpr const char* typeName(Primitive*) { return "Primitive"; }

  template <typename T, typename MapT>
  bool addObjectData(MapT& map, const T& data, const char* type) {
    if (data.name.empty()) return error("Scene", "addEntity", std::string(type) + " name is empty");
    std::pair<typename MapT::iterator, bool> res = map.emplace(data.name, data);
    if (!res.second) return error("Scene", "addObject", std::string(type) + " name already used: " + data.name);
    return true;
  }

  std::map<std::string, Model>& getObjects(Model*) { return models; }
  const std::map<std::string, Model>& getObjects(Model*) const { return models; }
  std::map<std::string, Camera>& getObjects(Camera*) { return cameras; }
  const std::map<std::string, Camera>& getObjects(Camera*) const { return cameras; }
  std::map<std::string, Light>& getObjects(Light*) { return lights; }
  const std::map<std::string, Light>& getObjects(Light*) const { return lights; }
  std::map<std::string, Grid>& getObjects(Grid*) { return grids; }
  const std::map<std::string, Grid>& getObjects(Grid*) const { return grids; }
  std::map<std::string, TextureData>& getObjects(TextureData*) { return textures; }
  const std::map<std::string, TextureData>& getObjects(TextureData*) const { return textures; }
  std::map<std::string, TextureConnection>& getObjects(TextureConnection*) { return textureConnections; }
  const std::map<std::string, TextureConnection>& getObjects(TextureConnection*) const { return textureConnections; }
  std::map<std::string, Primitive>& getObjects(Primitive*) { return primitives; }
  const std::map<std::string, Primitive>& getObjects(Primitive*) const { return primitives; }
};