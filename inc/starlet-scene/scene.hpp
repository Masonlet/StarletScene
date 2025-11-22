#pragma once

#include "starlet-scene/manager/entity_manager.hpp"
#include "starlet-scene/manager/component_manager.hpp"
#include "starlet-scene/manager/system_manager.hpp"

#include "starlet-math/vec4.hpp"

namespace Starlet::Scene {
	class Scene {
	public:
		void setScenePath(const std::string& path) { this->path = path; }
		const std::string& getScenePath() const { return path; }

		void setAmbientLight(const Math::Vec4<float>& color) { ambientLight = color; }
		const Math::Vec4<float>& getAmbientLight() const { return ambientLight; }

		Entity createEntity() {
			return entityManager.createEntity();
		}

		const std::vector<Entity>& getEntities() const {
			return entityManager.getEntities();
		}

		template<typename T>
		bool hasComponent(Entity entity) const {
			return componentManager.hasComponent<T>(entity);
		}

		template<typename T, typename... Args>
		T* addComponent(Entity entity, Args&&... args) {
			return componentManager.addComponent<T>(entity, std::forward<Args>(args)...);
		}

		template<typename T>
		T& getComponent(Entity entity) {
			return componentManager.getComponent<T>(entity);
		}

		template<typename T>
		const T& getComponent(Entity entity) const {
			return componentManager.getComponent<T>(entity);
		}

		template<typename T>
		std::vector<std::pair<Entity, T*>> getEntitiesOfType() {
			return componentManager.getEntitiesOfType<T>();
		}

		template<typename T>
		std::vector<std::pair<Entity, const T*>> getEntitiesOfType() const {
			return componentManager.getEntitiesOfType<T>();
		}

		template<typename T>
		std::vector<T*> getComponentsOfType() {
			return componentManager.getComponentsOfType<T>();
		}

		template<typename T>
		std::vector<const T*> getComponentsOfType() const {
			return componentManager.getComponentsOfType<T>();
		}

		template<typename T>
		T* getComponentByName(const std::string& name) {
			return componentManager.getComponentByName<T>(name);
		}

		template<typename T>
		const T* getComponentByName(const std::string& name) const {
			return componentManager.getComponentByName<T>(name);
		}

		template<typename T>
		Entity getEntityByName(const std::string& name) {
			return componentManager.getEntityByName<T>(name);
		}

		template<typename T>
		const Entity getEntityByName(const std::string& name) const {
			return componentManager.getEntityByName<T>(name);
		}

		template<typename T>
		T* getComponentByIndex(const size_t index) {
			return componentManager.getComponentByIndex<T>(index);
		}

		template<typename T>
		const T* getComponentByIndex(const size_t index) const {
			return componentManager.getComponentByIndex<T>(index);
		}

		void registerSystem(std::unique_ptr<ISystem> system) {
			systemManager.registerSystem(std::move(system));
		}

		void updateSystems(Input::InputManager& input, float deltaTime) {
			systemManager.updateSystems(*this, input, deltaTime);
		}

	private:
		std::string path;
		Math::Vec4<float> ambientLight{ 0.0f, 0.0f, 0.0f, 1.0f };

		EntityManager entityManager;
		ComponentManager componentManager;
		SystemManager systemManager;
	};
}