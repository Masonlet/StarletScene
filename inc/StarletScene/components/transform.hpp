#pragma once

#include "component.hpp"
#include "StarletMath/vec3.hpp"

struct Transform : public IStarComponent {
	Vec3<float> pos{ 0.0f };
	Vec3<float> rot{ 0.0f };
	Vec3<float> scale{ 1.0f };
};