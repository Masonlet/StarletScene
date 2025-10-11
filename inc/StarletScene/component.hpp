#pragma once

#include "StarletScene/entity.hpp"

#include <string>

struct IStarComponent {
	virtual ~IStarComponent() = default;
	StarEntity id{ 0 };
};

struct NamedComponent : public IStarComponent {
	std::string name;
};