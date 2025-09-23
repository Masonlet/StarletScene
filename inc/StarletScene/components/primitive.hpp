#pragma once

#include "component.hpp"
#include "StarletMath/transform.hpp"
#include "StarletMath/vec4.hpp"
#include "colour.hpp"
#include <string>

enum class PrimitiveType {
	Triangle,
	Square,
	Cube
};

struct Primitive : public IStarComponent {
	std::string name;
	PrimitiveType type;
	Transform transform;
	Vec4<float> colour;
	ColourMode colourMode;
};