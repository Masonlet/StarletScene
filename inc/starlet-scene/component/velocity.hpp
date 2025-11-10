#pragma once

#include "starlet-scene/component.hpp"

#include "starlet-math/vec3.hpp"

namespace Starlet::Scene {
	struct VelocityComponent : public IStarComponent {
		Math::Vec3<float> velocity{ 1.0f };
	};
}