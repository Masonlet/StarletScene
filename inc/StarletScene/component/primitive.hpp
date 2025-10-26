#pragma once

#include "StarletScene/component.hpp"

#include <string>

namespace Starlet::Scene {
	enum class PrimitiveType {
		Triangle,
		Square,
		Cube
	};

	struct Primitive : public NamedComponent {
		PrimitiveType type;
	};
}