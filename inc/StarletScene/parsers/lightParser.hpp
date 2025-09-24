#pragma once

struct Light;
struct TransformComponent;
bool parseLight(const unsigned char*& p, Light& light, TransformComponent& transform);
