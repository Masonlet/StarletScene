#pragma once

#include "component.hpp"
#include <string>

struct Camera : public IStarComponent {
	std::string name;
	float moveSpeed{ 25.0f }, mouseSpeed{ 0.1f };

	float fov{ 60.0f };
	float nearPlane{ 0.1f }, farPlane{ 10000.0f };
	bool enabled{ true }, paused{ false };
	float lastX{ 0.0f }, lastY{ 0.0f };
};