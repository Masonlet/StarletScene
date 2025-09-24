#pragma once

struct TransformComponent;

struct Primitive;
enum class PrimitiveType;
template<PrimitiveType T>
bool parsePrimitive(const unsigned char*& p, Primitive& out, TransformComponent& transform);

bool parseTriangle(const unsigned char*& p, Primitive& out, TransformComponent& transform);
bool parseSquare(const unsigned char*& p, Primitive& out, TransformComponent& transform);
bool parseCube(const unsigned char*& p, Primitive& out, TransformComponent& transform);