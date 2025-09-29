#pragma once

#include "StarletScene/component.hpp"
#include "colour.hpp"

#include "StarletMath/vec4.hpp"
#include "StarletMath/transform.hpp"

#include <string>

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
