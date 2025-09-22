#pragma once

#include "starletmath/vec4.hpp"
#include "starletmath/transform.hpp"
#include "colour.hpp"
#include <string>

enum class GridType {
	Square,
	Cube,
	Model
};

struct Grid {
	std::string name;
	GridType type;
	unsigned int count{ 1 };
	float spacing{ 1.0f };
	Transform transform;
	Vec4<float> colour{ 1.0f };
	ColourMode colourMode{ ColourMode::Solid };
};
