#pragma once

#include "StarletScene/component.hpp"

#include "StarletMath/vec2.hpp"
#include "StarletMath/vec3.hpp"
#include "StarletMath/vec4.hpp"

#include <string>

struct Light : public NamedComponent {
	Vec4<float> attenuation{ 0.0f, 0.01f, 0.01f, 1.0f }; // x = constant, y = linear, z = quadratic, w = cutoff distance
	unsigned int type{ 0 };															 // 0 = Point, 1 = Spot, 2 = Directional
	Vec2<float> param1{ 0.0f };													 // x = inner angle (spot), y = outer angle (spot)
	bool enabled{ true };																 // Light enabled
};
