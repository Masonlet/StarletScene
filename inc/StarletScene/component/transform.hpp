#pragma once

#include "StarletScene/component.hpp"

#include "StarletMath/vec3.hpp"

namespace Starlet::Scene {
	struct TransformComponent : public IStarComponent {
		TransformComponent() : pos(0.0f), rot(0.0f), size(1.0f) {};
		TransformComponent(Math::Vec3<float> pos, Math::Vec3<float> rot, Math::Vec3<float> size) : pos(pos), rot(rot), size(size) {}

		Math::Vec3<float> pos;
		Math::Vec3<float> rot;
		Math::Vec3<float> size;
	};
}