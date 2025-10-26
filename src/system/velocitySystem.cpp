#include "StarletScene/system/velocitySystem.hpp"

#include "StarletScene/component/transform.hpp"
#include "StarletScene/component/velocity.hpp"

#include "StarletControls/inputManager.hpp"
#include "StarletScene/scene.hpp"

#include "StarletMath/constants.hpp"

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