#include "StarletScene/objects/textureData.hpp"
#include "StarletScene/objects/textureConnection.hpp"
#include "StarletScene/parsers/textureParser.hpp"
#include "StarletParsers/parserUtils.hpp"

bool parseTexture(const unsigned char*& p, TextureData& out) {
  PARSE_STRING_OR(return false, p, out.name, 128, "texture name");
  PARSE_STRING_OR(return false, p, out.faces[0], 256, "texture file");
  PARSE_OR(return false, parseFloat, out.mix, "texture mix");
  PARSE_OR(return false, parseVec2, out.tiling, "texture tiling");
  out.isCube = false;
  return true;
}
bool parseCubeTexture(const unsigned char*& p, TextureData& out) {
  PARSE_STRING_OR(return false, p, out.name, 128, "cube map name");
  for (int i = 0; i < 6; ++i) PARSE_STRING_OR(return false, p, out.faces[i], 256, "cube map face");
  PARSE_OR(return false, parseFloat, out.mix, "cube map mix");
  PARSE_OR(return false, parseVec2, out.tiling, "cube map tiling");
  out.isCube = true;
  return true;
}
bool parseTextureConnection(const unsigned char*& p, TextureConnection& out) {
  PARSE_STRING_OR(return false, p, out.modelName, 64, "texture connection model name");
  PARSE_OR(return false, parseUInt, out.slot, "texture connection slot");
  PARSE_STRING_OR(return false, p, out.textureName, 128, "texture connection name");
  PARSE_OR(return false, parseFloat, out.mix, "texture connection mix");
  out.name = out.modelName + out.textureName + "_" + std::to_string(out.slot);
  return true;
}
