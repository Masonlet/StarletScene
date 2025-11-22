#pragma once

#include "starlet-scene/component.hpp"

#include "starlet-graphics/resource/resource_handle.hpp"

#include "starlet-math/vec2.hpp"

#include <string>

namespace Starlet::Scene {
	enum class ColourMode {
		Solid,
		Random,
		VerticalGradient,
		PLYColour
	};

	struct Model : public NamedComponent {
		std::string meshPath;
		Graphics::ResourceHandle meshHandle;

		bool isVisible{ true }, isLighted{ true }, useTextures{ false };
		ColourMode mode{ ColourMode::Solid };

		static const unsigned int NUM_TEXTURES = 4;
		std::string textureNames[NUM_TEXTURES]{ "" };
		float textureMixRatio[NUM_TEXTURES]{ 1.0f, 0.0f, 0.0f, 0.0f };
		Math::Vec2<float> textureTiling{ 1.0f, 1.0f };
		Graphics::ResourceHandle textureHandles[NUM_TEXTURES];
	};
}