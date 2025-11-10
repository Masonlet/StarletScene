#include "starlet-scene/system/cameraFovSystem.hpp"

#include "starlet-scene/component/camera.hpp"
#include "starlet-scene/component/transform.hpp"

#include "starlet-controls/inputManager.hpp"
#include "starlet-scene/scene.hpp"

#include <GLFW/glfw3.h>
#include <cmath>

namespace Starlet::Scene {
  void CameraFovSystem::update(Scene& scene, Input::InputManager& input, const float deltaTime) {
    std::vector<Input::ScrollEvent> scrollEvents = input.consumeScrollEvents();
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
}