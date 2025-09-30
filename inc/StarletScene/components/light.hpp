#pragma once

#include "StarletScene/component.hpp"

#include "StarletMath/vec2.hpp"
#include "StarletMath/vec4.hpp"

enum class LightType {
	Point,
	Spot,
	Directional
};

struct Light : public NamedComponent {
	bool enabled{ true };												
	LightType type{ LightType::Point };
	Vec4<float> attenuation{ 0.0f, 0.01f, 0.01f, 1.0f }; // x = constant, y = linear, z = quadratic, w = cutoff distance
	Vec2<float> param1{ 0.0f };													 // x = inner angle (spot), y = outer angle (spot)
};
