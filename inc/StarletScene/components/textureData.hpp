#pragma once

#include "component.hpp"
#include "starletmath/vec2.hpp"
#include <string>

struct TextureData : public IStarComponent {
	std::string name;
	std::string faces[6];

	float mix{ 1.0f };
	Vec2<float> tiling{ 1.0f, 1.0f };
	bool isCube{ false };
};