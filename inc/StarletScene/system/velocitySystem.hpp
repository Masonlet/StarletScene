#pragma once

#include "StarletScene/system.hpp"

struct VelocitySystem : public ISystem {
	void update(Scene& scene, InputManager& input, const float deltaTime) override;
};
