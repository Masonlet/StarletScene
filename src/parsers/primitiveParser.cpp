#include "StarletScene/parsers/primitiveParser.hpp"

#include "StarletScene/components/primitive.hpp"

#include "StarletParsers/parserUtils.hpp"
#include "StarletScene/parsers/colourParser.hpp"

template<PrimitiveType T>
bool parsePrimitive(const unsigned char*& p, Primitive& out) {
  out.type = T;
  PARSE_STRING_OR(return false, p, out.name, 64, "primitive name");
  Vec3<float> temp;
  PARSE_OR(return false, parseVec3, temp, "primitive position");
  out.transform.pos = { temp, 1.0f };
  PARSE_OR(return false, parseVec3, out.transform.rot, "primitive rotation");
  PARSE_OR(return false, parseVec3, out.transform.size, "triangle size");
  return parseColour(p, out.colour, out.colourMode);
}

bool parseTriangle(const unsigned char*& p, Primitive& out) {
  return parsePrimitive<PrimitiveType::Triangle>(p, out);
}
bool parseSquare(const unsigned char*& p, Primitive& out) {
  return parsePrimitive<PrimitiveType::Square>(p, out);
}
bool parseCube(const unsigned char*& p, Primitive& out) {
  return parsePrimitive<PrimitiveType::Cube>(p, out);
}