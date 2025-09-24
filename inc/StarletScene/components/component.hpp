#pragma once

#include <cstdint>

using StarEntity = uint32_t;

struct IStarComponent {
	virtual ~IStarComponent() = default;
	StarEntity id;
};
