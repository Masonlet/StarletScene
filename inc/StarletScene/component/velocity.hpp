#pragma once

#include "StarletScene/component.hpp"

#include "StarletMath/vec3.hpp"

namespace Starlet::Scene {
	struct VelocityComponent : public IStarComponent {
		Math::Vec3<float> velocity{ 1.0f };
	};
}