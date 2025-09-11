#pragma once

struct Grid;
template <GridType T>
bool parseGrid(const unsigned char*& p, Grid& out);

bool parseSquareGrid(const unsigned char*& p, Grid& out);
bool parseCubeGrid(const unsigned char*& p, Grid& out);
