#pragma once

struct Grid;
enum class GridType;

template <GridType T>
bool parseGrid(const unsigned char*& p, Grid& out);

bool parseSquareGrid(const unsigned char*& p, Grid& out);
bool parseCubeGrid(const unsigned char*& p, Grid& out);