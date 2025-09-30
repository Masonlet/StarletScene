#include "StarletScene/systems/cameraFovSystem.hpp"

#include "StarletScene/components/camera.hpp"
#include "StarletScene/components/transform.hpp"

#include "StarletControls/inputManager.hpp"
#include "StarletScene/scene.hpp"

#include <GLFW/glfw3.h>
#include <cmath>

void CameraFovSystem::update(Scene& scene, InputManager& input, const float deltaTime) {
  float scrollDelta = static_cast<float>(input.consumeScrollY());
  if (scrollDelta == 0.0f) return;

  for (auto& [entity, camera] : scene.getEntitiesOfType<Camera>()) {
    camera->fov -= scrollDelta;
    if (camera->fov < 1.0f)   camera->fov = 1.0f;
    if (camera->fov > 120.0f) camera->fov = 120.0f;
  }
}