#include "StarletScene/parsers/lightParser.hpp"

#include "StarletScene/components/light.hpp"

#include "StarletParsers/parserUtils.hpp"
#include "StarletParsers/utils/log.hpp"

static bool parseLightType(const unsigned char*& p, unsigned int& typeOut) {
	p = skipWhitespace(p);
	if (!p || *p == '\0') return false;
	if (*p == '0') { ++p; typeOut = 0; return true; }
	if (*p == '1') { ++p; typeOut = 1; return true; }
	if (*p == '2') { ++p; typeOut = 2; return true; }

	const unsigned char* original = p;
	if (parseUInt(p, typeOut)) return true;

	p = original;
	unsigned char typeName[64]{};
	if (!parseToken(p, typeName, sizeof(typeName)) || !p) {
		p = original;
		return false;
	}

	if (strcmp((char*)typeName, "Point") == 0)       typeOut = 0;
	else if (strcmp((char*)typeName, "Spot") == 0)        typeOut = 1;
	else if (strcmp((char*)typeName, "Directional") == 0) typeOut = 2;
	else return error("Parser", "parseLightType", "Unknown light type");
	return true;
}

bool parseLight(const unsigned char*& p, Light& out) {
  PARSE_OR(return false, parseBool, out.enabled, "light enabled");
  PARSE_STRING_OR(return false, p, out.name, 64, "light name");
  PARSE_OR(return false, parseLightType, out.type, "light type");
  PARSE_OR(return false, parseVec3, out.pos, "light position");
  PARSE_OR(return false, parseVec4, out.diffuse, "light diffuse");
  PARSE_OR(return false, parseVec4, out.attenuation, "light attenuation");
  PARSE_OR(return false, parseVec3, out.direction, "light direction");
  PARSE_OR(return false, parseVec2f, out.param1, "light param1");
  return true;
}