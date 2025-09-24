#pragma once

struct Grid;
enum class GridType;

struct TransformComponent;

template <GridType T>
bool parseGrid(const unsigned char*& p, Grid& grid, TransformComponent& transform);

bool parseSquareGrid(const unsigned char*& p, Grid& grid, TransformComponent& transform);
bool parseCubeGrid(const unsigned char*& p, Grid& grid, TransformComponent& transform);