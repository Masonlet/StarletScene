#include "StarletScene/parsers/velocityParser.hpp"

#include "StarletScene/components/velocity.hpp"

#include "StarletParsers/parserUtils.hpp"
#include "StarletParsers/utils/log.hpp"

bool parseVelocity(const unsigned char*& p, VelocityComponent& velocity) {
	PARSE_OR(return false, parseVec3, velocity.velocity, "velocity");
	return true;
}