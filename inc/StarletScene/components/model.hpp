#pragma once

#include "component.hpp"
#include "colour.hpp"

#include "StarletMath/vec2.hpp"
#include "StarletMath/vec3.hpp"
#include "StarletMath/vec4.hpp"
#include "StarletMath/mat4.hpp"

#include <string>

struct Model : public IStarComponent {
	std::string name;
	std::string meshPath;

	Vec4<float> colour{ 1.0f }, specular{ 1.0f, 1.0f, 1.0f, 32.0f };
	ColourMode colourMode{ ColourMode::Solid };
	bool isVisible{ true }, isLighted{ true }, useTextures{ false };

	static const unsigned int NUM_TEXTURES = 4;
	std::string textureNames[NUM_TEXTURES]{ "" };
	float textureMixRatio[NUM_TEXTURES]{ 1.0f, 0.0f, 0.0f, 0.0f };
	Vec2<float> textureTiling{ 1.0f, 1.0f };
};