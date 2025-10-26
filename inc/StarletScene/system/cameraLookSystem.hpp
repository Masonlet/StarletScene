#pragma once

#include "StarletScene/system.hpp"

namespace Starlet::Scene {
	struct CameraLookSystem : public ISystem {
		void update(Scene& scene, Input::InputManager& input, const float deltaTime) override;
	};
}
