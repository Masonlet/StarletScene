#include "starlet-scene/system/cameraLookSystem.hpp"

#include "starlet-scene/component/camera.hpp"
#include "starlet-scene/component/transform.hpp"

#include "starlet-controls/inputManager.hpp"
#include "starlet-scene/scene.hpp"

#include <GLFW/glfw3.h>
#include <cmath>

namespace Starlet::Scene {
  void CameraLookSystem::update(Scene& scene, Input::InputManager& input, const float deltaTime) {
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
}