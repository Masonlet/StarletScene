#pragma once

#include "starlet-scene/entity.hpp"

#include <string>

namespace Starlet::Scene {
	struct IStarComponent {
		virtual ~IStarComponent() = default;
		Entity id{ 0 };
	};

	struct NamedComponent : public IStarComponent {
		std::string name;
	};
}