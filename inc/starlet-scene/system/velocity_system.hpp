#pragma once

#include "starlet-scene/system.hpp"

namespace Starlet::Scene {
	struct VelocitySystem : public ISystem {
		void update(Scene& scene, Input::InputManager& input, const float deltaTime) override;
	};
}