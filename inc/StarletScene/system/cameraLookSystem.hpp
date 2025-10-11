#pragma once

#include "StarletScene/system.hpp"

struct CameraLookSystem : public ISystem {
	void update(Scene& scene, InputManager& input, const float deltaTime) override;
};

