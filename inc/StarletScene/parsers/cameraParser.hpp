#pragma once

struct Camera;
struct TransformComponent;

bool parseCamera(const unsigned char*& p, Camera& out, TransformComponent& transform);