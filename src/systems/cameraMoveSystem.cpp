#include "StarletScene/systems/cameraMoveSystem.hpp"

#include "StarletScene/components/camera.hpp"
#include "StarletScene/components/transform.hpp"

#include "StarletControls/inputManager.hpp"
#include "StarletScene/scene.hpp"

#include "StarletMath/constants.hpp"

#include <GLFW/glfw3.h>
#include <cmath>

void CameraMoveSystem::update(Scene& scene, InputManager& input, const float deltaTime) {
  for (auto& [entity, camera] : scene.getEntitiesOfType<Camera>()) {
    if (!camera->enabled) continue;

    if (!scene.hasComponent<TransformComponent>(entity)) continue;
    TransformComponent& transform = scene.getComponent<TransformComponent>(entity);

    const float yaw = transform.rot.y;
    const float pitch = transform.rot.x;

    Vec3<float> front;
    front.x = cos(radians(yaw)) * cos(radians(pitch));
    front.y = sin(radians(pitch));
    front.z = sin(radians(yaw)) * cos(radians(pitch));
    front = front.normalized();

    Vec3<float> right = front.cross(WORLD_UP).normalized();
    Vec3<float> up = right.cross(front).normalized();

    const float s = camera->moveSpeed * deltaTime;
    if (input.isKeyDown(GLFW_KEY_W)) transform.pos += front * s;
    if (input.isKeyDown(GLFW_KEY_A)) transform.pos -= right * s;
    if (input.isKeyDown(GLFW_KEY_S)) transform.pos -= front * s;
    if (input.isKeyDown(GLFW_KEY_D)) transform.pos += right * s;
    if (input.isKeyDown(GLFW_KEY_SPACE)) transform.pos += up * s;
    if (input.isKeyDown(GLFW_KEY_LEFT_CONTROL)) transform.pos -= up * s;
  }
}