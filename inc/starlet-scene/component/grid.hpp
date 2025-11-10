#pragma once

#include "starlet-scene/component.hpp"

#include <string>

namespace Starlet::Scene {
	enum class GridType {
		Square,
		Cube,
		Model
	};

	struct Grid : public NamedComponent {
		GridType type{ GridType::Cube };
		unsigned int count{ 1 };
		float spacing{ 1.0f };
	};
}