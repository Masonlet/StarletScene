#pragma once

#include "StarletScene/component.hpp"

#include "StarletGraphics/resource/meshHandle.hpp"
#include "StarletGraphics/resource/textureHandle.hpp"

#include "StarletMath/vec2.hpp"

#include <string>

enum class ColourMode {
	Solid,
	Random,
	VerticalGradient,
	PLYColour
};

struct Model : public NamedComponent {
	std::string meshPath;
	MeshHandle meshHandle;

	bool isVisible{ true }, isLighted{ true }, useTextures{ false };
	ColourMode mode{ ColourMode::Solid };

	static const unsigned int NUM_TEXTURES = 4;
	std::string textureNames[NUM_TEXTURES]{ "" };
	float textureMixRatio[NUM_TEXTURES]{ 1.0f, 0.0f, 0.0f, 0.0f };
	Vec2<float> textureTiling{ 1.0f, 1.0f };
	TextureHandle textureHandles[NUM_TEXTURES];
};