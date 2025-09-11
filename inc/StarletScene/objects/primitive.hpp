#pragma once

#include <string>
#include <StarletMath/transform.hpp>
#include <StarletMath/vec4.hpp>
#include "colour.hpp"

enum class PrimitiveType {
	Triangle,
	Square,
	Cube
};

struct Primitive {
	std::string name;
	PrimitiveType type;
	Transform transform;
	Vec4 colour;
	ColourMode colourMode;
};