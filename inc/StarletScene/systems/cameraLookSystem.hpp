#pragma once

#include "StarletScene/system.hpp"

class Scene;
class InputManager;

struct CameraLookSystem : public ISystem {
	void update(Scene& scene, InputManager& input, const float deltaTime) override;
};

