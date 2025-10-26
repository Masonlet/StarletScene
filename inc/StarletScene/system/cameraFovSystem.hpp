#pragma once

#include "StarletScene/system.hpp"

namespace Starlet::Scene {
	struct CameraFovSystem : public ISystem {
		void update(Scene& scene, Input::InputManager& input, const float deltaTime) override;
	};
}
