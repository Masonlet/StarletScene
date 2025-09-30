#pragma once

#include "StarletScene/component.hpp"

enum class ColourMode {
  Solid,
  Random,
  VerticalGradient,
  PLYColour
};

#include "StarletMath/vec4.hpp"

struct ColourComponent : public IStarComponent {
  ColourComponent() : colour(1.0f), specular(1.0f, 1.0f, 1.0f, 32.0f) {}

  Vec4<float> colour;
  Vec4<float> specular;
};