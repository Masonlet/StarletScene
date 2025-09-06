#pragma once

#include <string>
#include <StarletMath/transform.hpp>
#include <StarletMath/vec4.hpp>
#include "colour.hpp"

struct Primitive {
	std::string name;

	Transform transform;
	Vec4 colour;
	ColourMode colourMode;
};