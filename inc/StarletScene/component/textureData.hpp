#pragma once

#include "StarletScene/component.hpp"

#include "StarletMath/vec2.hpp"

#include <string>

namespace Starlet::Scene {
	struct TextureData : public NamedComponent {
		std::string faces[6];
		float mix{ 1.0f };
		Math::Vec2<float> tiling{ 1.0f, 1.0f };
		bool isCube{ false };
	};
}