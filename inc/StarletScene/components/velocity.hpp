#pragma once

#include "component.hpp"

#include "StarletMath/vec3.hpp"

struct VelocityComponent : public IStarComponent {
	Vec3<float> velocity{ 1.0f };
};