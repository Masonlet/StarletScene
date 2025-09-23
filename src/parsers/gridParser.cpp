#include "StarletScene/components/grid.hpp"
#include "StarletScene/parsers/gridParser.hpp"
#include "StarletScene/parsers/colourParser.hpp"
#include "StarletParsers/parserUtils.hpp"

template <GridType T>
bool parseGrid(const unsigned char*& p, Grid& out) {
  out.type = T;
  PARSE_STRING_OR(return false, p, out.name, 64, "grid name");
  PARSE_OR(return false, parseUInt, out.count, "grid count");
  PARSE_OR(return false, parseFloat, out.spacing, "grid spacing");
  Vec3<float> temp;
  PARSE_OR(return false, parseVec3, temp, "grid start position");
  out.transform.pos = { temp, 1.0f };
  PARSE_OR(return false, parseVec3, out.transform.rot, "grid rotation");
  PARSE_OR(return false, parseVec3, out.transform.size, "grid scale");
  return parseColour(p, out.colour, out.colourMode);
}

bool parseSquareGrid(const unsigned char*& p, Grid& out) { 
  return parseGrid<GridType::Square>(p, out); 
}
bool parseCubeGrid(const unsigned char*& p, Grid& out) { 
  return parseGrid<GridType::Cube>(p, out); 
}
