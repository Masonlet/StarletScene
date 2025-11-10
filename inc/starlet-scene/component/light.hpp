#pragma once

#include "starlet-scene/component.hpp"

#include "starlet-math/vec2.hpp"
#include "starlet-math/vec4.hpp"

namespace Starlet::Scene {
	enum class LightType {
		Point,
		Spot,
		Directional
	};

	struct Light : public NamedComponent {
		bool enabled{ true };
		LightType type{ LightType::Point };
		Math::Vec4<float> attenuation{ 0.0f, 0.01f, 0.01f, 1.0f }; // x = constant, y = linear, z = quadratic, w = cutoff distance
		Math::Vec2<float> param1{ 0.0f };													 // x = inner angle (spot), y = outer angle (spot)
	};
}