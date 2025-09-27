#pragma once

#include "component.hpp"

#include "StarletMath/vec3.hpp"

struct TransformComponent : public IStarComponent {
	TransformComponent() : pos(0.0f), rot(0.0f), size(1.0f) {};
	TransformComponent(Vec3<float> pos, Vec3<float> rot, Vec3<float> size): pos(pos), rot(rot), size(size) {}

	Vec3<float> pos;
	Vec3<float> rot;
	Vec3<float> size;
};