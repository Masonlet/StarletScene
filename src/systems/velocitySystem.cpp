#include "StarletScene/systems/velocitySystem.hpp"

#include "StarletScene/components/transform.hpp"
#include "StarletScene/components/velocity.hpp"

#include "StarletControls/inputManager.hpp"
#include "StarletScene/scene.hpp"

#include "StarletMath/constants.hpp"

void VelocitySystem::update(Scene& scene, InputManager& input, const float deltaTime) {
  for (auto& [entity, velocity] : scene.getEntitiesOfType<VelocityComponent>()) {
    if (scene.hasComponent<TransformComponent>(entity)) {
      TransformComponent& transform = scene.getComponent<TransformComponent>(entity);
      transform.pos += velocity->velocity * deltaTime;
    }
  }
}