#pragma once

template <typename T> struct Vec4;
enum class ColourMode;
bool parseColour(const unsigned char*& p, Vec4<float>& colourOut, ColourMode& modeOut);