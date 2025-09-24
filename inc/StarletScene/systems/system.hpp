#pragma once

class Scene;
class InputManager;

struct ISystem {
	virtual ~ISystem() = default;
	virtual void update(Scene& scene, InputManager& input, const float deltaTime) = 0;
};