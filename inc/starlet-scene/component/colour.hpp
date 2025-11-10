#pragma once

#include "starlet-scene/component.hpp"

#include "starlet-math/vec4.hpp"

namespace Starlet::Scene {
  struct ColourComponent : public IStarComponent {
    ColourComponent() : colour(1.0f), specular(1.0f, 1.0f, 1.0f, 32.0f) {}

    Math::Vec4<float> colour;
    Math::Vec4<float> specular;
  };
}