#pragma once

namespace Starlet {
	namespace Input {
		class InputManager;
	}

	namespace Scene {
		class Scene;

		struct ISystem {
			virtual ~ISystem() = default;
			virtual void update(Scene& scene, Input::InputManager& input, const float deltaTime) = 0;
		};
	}
}