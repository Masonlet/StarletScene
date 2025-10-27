#pragma once

#include "StarletScene/component.hpp"
#include "StarletSerializer/utils/log.hpp"

#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>

namespace Starlet::Scene {
	class ComponentManager {
	public:
		template<typename T>
		bool hasComponent(Entity entity) const {
			auto it = entityComponents.find(entity);
			if (it == entityComponents.end()) return false;
			return it->second.find(typeid(T).hash_code()) != it->second.end();
		}

		template<typename T, typename... Args>
		T* addComponent(Entity entity, Args&&... args) {
			if (hasComponent<T>(entity)) {
				Serializer::error("ComponentManager", "addComponent", "Entity already has this component");
				return nullptr;
			}

			auto component = std::make_unique<T>(std::forward<Args>(args)...);
			T* rawPtr = component.get();
			rawPtr->id = entity;
			entityComponents[entity][typeid(T).hash_code()] = std::move(component);
			return rawPtr;
		}

		template<typename T>
		T& getComponent(Entity entity) {
			auto& components = entityComponents.at(entity);
			auto it = components.find(typeid(T).hash_code());
			if (it == components.end()) {
				Serializer::error("ComponentManager", "getComponent", "Component not found for entity");
				throw std::runtime_error("Failed to get component");
			}
			return *static_cast<T*>(it->second.get());
		}
		template<typename T>
		const T& getComponent(Entity entity) const {
			const auto& components = entityComponents.at(entity);
			auto it = components.find(typeid(T).hash_code());
			if (it == components.end()) {
				Serializer::error("ComponentManager", "getComponent", "Component not found for entity");
				throw std::runtime_error("Failed to get component");
			}
			return *static_cast<const T*>(it->second.get());
		}

		template<typename T>
		std::vector<std::pair<Entity, T*>> getEntitiesOfType() {
			std::vector<std::pair<Entity, T*>> entitiesOut;
			for (auto& [entity, components] : entityComponents) {
				auto it = components.find(typeid(T).hash_code());
				if (it != components.end()) entitiesOut.emplace_back(entity, static_cast<T*>(it->second.get()));
			}
			return entitiesOut;
		}
		template<typename T>
		std::vector<std::pair<Entity, const T*>> getEntitiesOfType() const {
			std::vector<std::pair<Entity, const T*>> entitiesOut;
			for (const auto& [entity, components] : entityComponents) {
				auto it = components.find(typeid(T).hash_code());
				if (it != components.end()) entitiesOut.emplace_back(entity, static_cast<const T*>(it->second.get()));
			}
			return entitiesOut;
		}

		template<typename T>
		std::vector<T*> getComponentsOfType() {
			std::vector<T*> componentsOut;
			for (auto& [entity, components] : entityComponents) {
				auto it = components.find(typeid(T).hash_code());
				if (it != components.end()) componentsOut.push_back(static_cast<T*>(it->second.get()));
			}
			return componentsOut;
		}
		template<typename T>
		std::vector<const T*> getComponentsOfType() const {
			std::vector<const T*> componentsOut;
			for (const auto& [entity, components] : entityComponents) {
				auto it = components.find(typeid(T).hash_code());
				if (it != components.end()) componentsOut.push_back(static_cast<const T*>(it->second.get()));
			}
			return componentsOut;
		}

		template<typename T>
		T* getComponentByName(const std::string& name) {
			for (T* component : getComponentsOfType<T>())
				if (component->name == name) return component;
			return nullptr;
		}
		template<typename T>
		const T* getComponentByName(const std::string& name) const {
			for (const T* component : getComponentsOfType<const T>())
				if (component->name == name) return component;
			return nullptr;
		}

		template<typename T>
		Entity getEntityByName(const std::string& name) {
			for (const auto& [entity, components] : entityComponents) {
				auto it = components.find(typeid(T).hash_code());
				if (it != components.end()) {
					const auto* e = static_cast<const T*>(it->second.get());
					if (e->name == name) return entity;
				}
			}
			return -1;
		}
		template <typename T>
		const Entity getEntityByName(const std::string& name) const {
			for (const auto& [entity, components] : entityComponents) {
				auto it = components.find(typeid(T).hash_code());
				if (it != components.end()) {
					const auto* e = static_cast<const T*>(it->second.get());
					if (e->name == name) return entity;
				}
			}
			return -1;
		}

		template<typename T>
		T* getComponentByIndex(const size_t index) {
			auto components = getComponentsOfType<T>();
			if (index < components.size()) return components[index];
			return nullptr;
		}
		template<typename T>
		const T* getComponentByIndex(const size_t index) const {
			auto components = getComponentsOfType<const T>();
			if (index < components.size()) return components[index];
			return nullptr;
		}

	private:
		std::unordered_map<Entity, std::unordered_map<size_t, std::unique_ptr<IStarComponent>>> entityComponents;
	};
}