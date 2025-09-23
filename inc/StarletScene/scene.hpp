#pragma once

#include "components/model.hpp"
#include "components/light.hpp"
#include "components/camera.hpp"
#include "components/grid.hpp"
#include "components/textureData.hpp"
#include "components/textureConnection.hpp"
#include "components/primitive.hpp"
#include "StarletParsers/utils/log.hpp"
#include "StarletMath/vec3.hpp"
#include "StarletMath/transform.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <iterator>
#include <stdexcept>
#include <memory>

using StarEntity = uint32_t;

class Scene {
public:
  inline void setScenePath(const std::string& path) { this->path = path; }
  const std::string& getScenePath() const { return path; }

	StarEntity createEntity() {
		StarEntity entity = nextEntity++;
		entities.push_back(entity);
		return entity;
	}

	template<typename T>
	bool hasComponent(StarEntity entity) const {
		auto entIt = entityComponents.find(entity);
		if (entIt == entityComponents.end()) return false;
		return entIt->second.find(typeid(T).hash_code()) != entIt->second.end();
	}

	template<typename T, typename... Args>
	T* addComponent(StarEntity entity, Args&&... args) {
		if (hasComponent<T>(entity)) {
			error("Scene", "addComponent", "Entity already has this component");
			return nullptr;
		}
		
		auto component = std::make_unique<T>(std::forward<Args>(args)...);
		T* rawPtr = component.get();
		entityComponents[entity][typeid(T).hash_code()] = std::move(component);
		return rawPtr;
	}

	template<typename T>
	T& getComponent(StarEntity entity) {
		auto& comps = entityComponents.at(entity);
		auto it = comps.find(typeid(T).hash_code());
		if (it == comps.end()) {
			error("Scene", "getComponent", "Component not found for entity");
			throw std::runtime_error("Failed to get component");
		}
		return *static_cast<T*>(it->second.get());
	}

	template<typename T>
	std::vector<std::pair<StarEntity, T*>> getEntitiesOfType() const {
		std::vector<std::pair<StarEntity, T*>> result;

		for (auto& [entity, comps] : entityComponents) {
			auto it = comps.find(typeid(T).hash_code());
			if (it != comps.end())  result.emplace_back(entity, static_cast<T*>(it->second.get()));
		}
		return result;
	}

	template<typename T>
	std::vector<T*> getComponentsOfType() const {
		std::vector<T*> components;
		for (const auto& [entity, comps] : entityComponents) {
			auto it = comps.find(typeid(T).hash_code());
			if (it != comps.end()) components.push_back(static_cast<T*>(it->second.get()));
		}
		return components;
	}

	template<typename T>
	T* getComponentByName(const std::string& name) const {
		for (T* comp : getComponentsOfType<T>()) if (comp->name == name) return comp;
		return nullptr;
	}

	template<typename T>
	T* getComponentByIndex(const size_t index) const {
		auto comps = getComponentsOfType<T>();
		if (index < comps.size()) return comps[index];
		return nullptr;
	}

private:
  std::string path;
	StarEntity nextEntity{ 0 };
	std::vector<StarEntity> entities;
	std::unordered_map<StarEntity, std::unordered_map<size_t, std::unique_ptr<IStarComponent>>> entityComponents; 
};