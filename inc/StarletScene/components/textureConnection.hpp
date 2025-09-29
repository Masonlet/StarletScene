#pragma once

#include "StarletScene/component.hpp"

#include <string>

struct TextureConnection : public NamedComponent {
	std::string modelName, textureName;
	unsigned int slot{ 0 };
	float mix{ 1.0f };
};