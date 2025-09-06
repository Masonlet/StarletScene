#include "StarletScene/objects/grid.hpp"
#include "StarletScene/parsers/gridParser.hpp"
#include "StarletScene/parsers/colourParser.hpp"
#include "StarletParsers/common/parserUtils.hpp"

bool parseGrid(const unsigned char*& p, Grid& out) {
  PARSE_OR(return false, parseUInt, out.count, "cubeGrid count");
  PARSE_OR(return false, parseFloat, out.spacing, "cubeGrid spacing");
  Vec3 temp;
  PARSE_OR(return false, parseVec3, temp, "cubeGrid start position");
  out.transform.pos = { temp, 1.0f };
  PARSE_OR(return false, parseVec3, out.transform.rot, "cubeGrid rotation");
  PARSE_OR(return false, parseVec3, out.transform.size, "cubeGrid scale");
  return parseColour(p, out.colour, out.colourMode);
}
