#include "StarletScene/system/cameraFovSystem.hpp"

#include "StarletScene/component/camera.hpp"
#include "StarletScene/component/transform.hpp"

#include "StarletControls/inputManager.hpp"
#include "StarletScene/scene.hpp"

#include <GLFW/glfw3.h>
#include <cmath>

void CameraFovSystem::update(Scene& scene, InputManager& input, const float deltaTime) {
	std::vector<ScrollEvent> scrollEvents = input.consumeScrollEvents();
  if (scrollEvents.empty()) return;

  double scrollDelta = 0.0;
  for (const auto& event : scrollEvents)
    scrollDelta += event.yOffset;
  if (scrollDelta == 0.0) return;

  for (auto& [entity, camera] : scene.getEntitiesOfType<Camera>()) {
    camera->fov -= static_cast<float>(scrollDelta);
    if (camera->fov < 1.0f)   camera->fov = 1.0f;
    if (camera->fov > 120.0f) camera->fov = 120.0f;
  }
}