#pragma once

#include "StarletScene/managers/entityManager.hpp"
#include "StarletScene/managers/componentManager.hpp"
#include "StarletScene/managers/systemManager.hpp"

#include "StarletMath/vec4.hpp"

class Scene {
public:
  void setScenePath(const std::string& path) { this->path = path; }
  const std::string& getScenePath() const { return path; }

  void setAmbientLight(const Vec4<float>& color) { ambientLight = color; }
	const Vec4<float>& getAmbientLight() const { return ambientLight; }

  StarEntity createEntity() {
    return entityManager.createEntity();
  }

  const std::vector<StarEntity>& getEntities() const {
    return entityManager.getEntities();
  }

	template<typename T>
	bool hasComponent(StarEntity entity) const {
		return componentManager.hasComponent<T>(entity);
	}

	template<typename T, typename... Args>
	T* addComponent(StarEntity entity, Args&&... args) {
		return componentManager.addComponent<T>(entity, std::forward<Args>(args)...);
	}

	template<typename T>
	T& getComponent(StarEntity entity) {
		return componentManager.getComponent<T>(entity);
	}

	template<typename T>
	const T& getComponent(StarEntity entity) const {
		return componentManager.getComponent<T>(entity);
	}

	template<typename T>
	std::vector<std::pair<StarEntity, T*>> getEntitiesOfType() {
		return componentManager.getEntitiesOfType<T>();
	}

	template<typename T>
	std::vector<std::pair<StarEntity, const T*>> getEntitiesOfType() const {
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
	StarEntity getEntityByName(const std::string& name) {
		return componentManager.getEntityByName<T>(name);
	}

	template<typename T>
	const StarEntity getEntityByName(const std::string& name) const {
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

	void updateSystems(InputManager& input, float deltaTime) {
		systemManager.updateSystems(*this, input, deltaTime);
	}

private:
  std::string path;
	Vec4<float> ambientLight{ 0.0f, 0.0f, 0.0f, 1.0f };

  EntityManager entityManager;
  ComponentManager componentManager;
  SystemManager systemManager;
};