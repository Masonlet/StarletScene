#pragma once

#include "component.hpp"
#include "StarletMath/vec4.hpp"
#include "StarletMath/transform.hpp"
#include "colour.hpp"
#include <string>

enum class GridType {
	Square,
	Cube,
	Model
};

struct Grid : public IStarComponent {
	std::string name;
	GridType type;
	unsigned int count{ 1 };
	float spacing{ 1.0f };
	Transform transform;
	Vec4<float> colour{ 1.0f };
	ColourMode colourMode{ ColourMode::Solid };
};
