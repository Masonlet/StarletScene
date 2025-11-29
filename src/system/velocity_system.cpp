#include "starlet-scene/system/velocity_system.hpp"

#include "starlet-scene/component/transform.hpp"
#include "starlet-scene/component/velocity.hpp"

#include "starlet-controls/input_manager.hpp"
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