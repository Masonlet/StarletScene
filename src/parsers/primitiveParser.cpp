#include "StarletScene/parsers/primitiveParser.hpp"

#include "StarletScene/components/primitive.hpp"
#include "StarletScene/components/transform.hpp"

#include "StarletParsers/parserUtils.hpp"
#include "StarletScene/parsers/colourParser.hpp"

template<PrimitiveType T>
bool parsePrimitive(const unsigned char*& p, Primitive& out, TransformComponent& transform) {
  out.type = T;
  PARSE_STRING_OR(return false, p, out.name, 64, "primitive name");
  PARSE_OR(return false, parseVec3, transform.pos, "primitive position");
  PARSE_OR(return false, parseVec3, transform.rot, "primitive rotation");
  PARSE_OR(return false, parseVec3, transform.size, "triangle size");
  return parseColour(p, out.colour, out.colourMode);
}

bool parseTriangle(const unsigned char*& p, Primitive& out, TransformComponent& transform) {
  return parsePrimitive<PrimitiveType::Triangle>(p, out, transform);
}
bool parseSquare(const unsigned char*& p, Primitive& out, TransformComponent& transform) {
  return parsePrimitive<PrimitiveType::Square>(p, out, transform);
}
bool parseCube(const unsigned char*& p, Primitive& out, TransformComponent& transform) {
  return parsePrimitive<PrimitiveType::Cube>(p, out, transform);
}