#pragma once

#include <cstdint>
#include <string>

using StarEntity = uint32_t;

struct IStarComponent {
	virtual ~IStarComponent() = default;
	StarEntity id;
};

struct NamedComponent : public IStarComponent {
	std::string name;
};