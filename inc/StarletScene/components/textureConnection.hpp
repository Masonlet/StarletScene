#pragma once

#include "component.hpp"
#include <string>

struct TextureConnection : public IStarComponent {
	std::string name;
	std::string modelName, textureName;
	unsigned int slot{ 0 };
	float mix{ 1.0f };
};