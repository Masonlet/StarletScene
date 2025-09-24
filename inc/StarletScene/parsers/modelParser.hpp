#pragma once

struct Model;
struct TransformComponent;
bool parseModel(const unsigned char*& p, Model& out, TransformComponent& transform);

