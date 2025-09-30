#include "StarletScene/systems/cameraLookSystem.hpp"

#include "StarletScene/components/camera.hpp"
#include "StarletScene/components/transform.hpp"

#include "StarletControls/inputManager.hpp"
#include "StarletScene/scene.hpp"

#include <GLFW/glfw3.h>
#include <cmath>

void CameraLookSystem::update(Scene& scene, InputManager& input, const float deltaTime) {
  if (!input.isCursorLocked()) return;

  for (auto& [entity, camera] : scene.getEntitiesOfType<Camera>()) {
    if (!camera->enabled) continue;

    if (scene.hasComponent<TransformComponent>(entity)) {
      TransformComponent& transform = scene.getComponent<TransformComponent>(entity);

      transform.rot.y += input.getMouseDelta().x * camera->mouseSpeed; 
      transform.rot.x += input.getMouseDelta().y * camera->mouseSpeed; 

      if (transform.rot.x > 89.0f)  transform.rot.x = 89.0f;
      if (transform.rot.x < -89.0f) transform.rot.x = -89.0f;
    }
  }
}