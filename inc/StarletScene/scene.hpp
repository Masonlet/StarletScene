#pragma once

#include "systems/system.hpp"
#include "components/component.hpp"

#include "StarletParsers/utils/log.hpp"

#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>

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
		rawPtr->id = entity;
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
	const T& getComponent(StarEntity entity) const {
		const auto& comps = entityComponents.at(entity);
		auto it = comps.find(typeid(T).hash_code());
		if (it == comps.end()) {
			error("Scene", "getComponent", "Component not found for entity");
			throw std::runtime_error("Failed to get component");
		}
		return *static_cast<const T*>(it->second.get());
	}

	template<typename T>
	std::vector<std::pair<StarEntity, T*>> getEntitiesOfType()  {
		std::vector<std::pair<StarEntity, T*>> entitiesOut;

		for (auto& [entity, comps] : entityComponents) {
			auto it = comps.find(typeid(T).hash_code());
			if (it != comps.end()) entitiesOut.emplace_back(entity, static_cast<T*>(it->second.get()));
		}
		return entitiesOut;
	}
	template<typename T>
	std::vector<std::pair<StarEntity, const T*>> getEntitiesOfType() const {
		std::vector<std::pair<StarEntity, const T*>> entitiesOut;
		for (const auto& [entity, comps] : entityComponents) {
			auto it = comps.find(typeid(T).hash_code());
			if (it != comps.end()) entitiesOut.emplace_back(entity, static_cast<const T*>(it->second.get()));
		}
		return entitiesOut;
	}

	template<typename T>
	std::vector<T*> getComponentsOfType() {
		std::vector<T*> components;
		for (auto& [entity, comps] : entityComponents) {
			auto it = comps.find(typeid(T).hash_code());
			if (it != comps.end()) components.push_back(static_cast<T*>(it->second.get()));
		}
		return components;
	}
	template<typename T>
	std::vector<const T*> getComponentsOfType() const {
		std::vector<const T*> components;
		for (const auto& [entity, comps] : entityComponents) {
			auto it = comps.find(typeid(T).hash_code());
			if (it != comps.end()) components.push_back(static_cast<const T*>(it->second.get()));
		}
		return components;
	}

	template<typename T>
	T* getComponentByName(const std::string& name) {
		for (T* comp : getComponentsOfType<T>()) if (comp->name == name) return comp;
		return nullptr;
	}
	template<typename T>
	const T* getComponentByName(const std::string& name) const {
		for (const T* comp : getComponentsOfType<const T>()) if (comp->name == name) return comp;
		return nullptr;
	}

	template<typename T>
	StarEntity getEntityByName(const std::string& name) {
		for (const auto& [entity, comps] : entityComponents) {
			auto it = comps.find(typeid(T).hash_code());
			if (it != comps.end()) {
				const auto* e = static_cast<const T*>(it->second.get());
				if (e->name == name) {
					return entity;
				}
			}
		}
		return -1; 
	}
	template <typename T>
	const StarEntity getEntityByName(const std::string& name) const {
		for (const auto& [entity, comps] : entityComponents) {
			auto it = comps.find(typeid(T).hash_code());
			if (it != comps.end()) {
				const auto* e = static_cast<const T*>(it->second.get());
				if (e->name == name) {
					return entity;
				}
			}
		}
		return -1; 
	}

	template<typename T>
	T* getComponentByIndex(const size_t index) {
		auto comps = getComponentsOfType<T>();
		if (index < comps.size()) return comps[index];
		return nullptr;
	}
	template<typename T>
	const T* getComponentByIndex(const size_t index) const {
		auto comps = getComponentsOfType<const T>();
		if (index < comps.size()) return comps[index];
		return nullptr;
	}

	void registerSystem(std::unique_ptr<ISystem> system) {
		if (system) systems.push_back(std::move(system));
		else error("Scene", "registerSystem", "Attempted to register invalid system");
	}
	void updateSystems(InputManager& input, float deltaTime) {
		for (const auto& system : systems) system->update(*this, input, deltaTime);
	}

private:
  std::string path;
	StarEntity nextEntity{ 0 };
	std::vector<StarEntity> entities;
	std::unordered_map<StarEntity, std::unordered_map<size_t, std::unique_ptr<IStarComponent>>> entityComponents; 
	std::vector<std::unique_ptr<ISystem>> systems;
};