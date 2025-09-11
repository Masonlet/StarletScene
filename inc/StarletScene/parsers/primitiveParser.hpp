#pragma once

struct Primitive;
template<PrimitiveType T>
bool parsePrimitive(const unsigned char*& p, Primitive& out);

bool parseTriangle(const unsigned char*& p, Primitive& out);
bool parseSquare(const unsigned char*& p, Primitive& out);
bool parseCube(const unsigned char*& p, Primitive& out);