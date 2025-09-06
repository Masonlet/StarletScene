#pragma once

struct Vec4;
enum class ColourMode;

bool parseColour(const unsigned char*& p, Vec4& colourOut, ColourMode& modeOut);