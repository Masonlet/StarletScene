#pragma once

#include "StarletScene/system.hpp"
#include "StarletSerializer/utils/log.hpp"

#include <vector>
#include <memory>

namespace Starlet::Scene {
	class SystemManager {
	public:
		void registerSystem(std::unique_ptr<ISystem> system) {
			if (system) systems.push_back(std::move(system));
			else Serializer::error("Scene", "registerSystem", "Attempted to register invalid system");
		}
		void updateSystems(Scene& scene, Input::InputManager& input, float deltaTime) {
			for (const std::unique_ptr<ISystem>& system : systems)
				system->update(scene, input, deltaTime);
		}

	private:
		std::vector<std::unique_ptr<ISystem>> systems;
	};
}