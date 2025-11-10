#include "starlet-scene/system/velocitySystem.hpp"

#include "starlet-scene/component/transform.hpp"
#include "starlet-scene/component/velocity.hpp"

#include "starlet-controls/inputManager.hpp"
#include "starlet-scene/scene.hpp"

#include "starlet-math/constants.hpp"

namespace Starlet::Scene {
  void VelocitySystem::update(Scene& scene, Input::InputManager& input, const float deltaTime) {
    for (auto& [entity, velocity] : scene.getEntitiesOfType<VelocityComponent>()) {
      if (scene.hasComponent<TransformComponent>(entity)) {
        TransformComponent& transform = scene.getComponent<TransformComponent>(entity);
        transform.pos += velocity->velocity * deltaTime;
      }
    }
  }
}