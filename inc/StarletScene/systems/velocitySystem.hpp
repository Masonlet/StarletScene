#pragma once

#include "system.hpp"

class Scene;
class InputManager;

struct VelocitySystem : public ISystem {
	void update(Scene& scene, InputManager& input, const float deltaTime) override;
};
