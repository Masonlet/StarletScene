#include "StarletScene/scene.hpp"
#include "StarletScene/sceneLoader.hpp"

#include "StarletScene/components/model.hpp"
#include "StarletScene/components/light.hpp"
#include "StarletScene/components/camera.hpp"
#include "StarletScene/components/grid.hpp"
#include "StarletScene/components/textureData.hpp"
#include "StarletScene/components/textureConnection.hpp"
#include "StarletScene/components/primitive.hpp"

#include "StarletScene/parsers/modelParser.hpp"
#include "StarletScene/parsers/lightParser.hpp"
#include "StarletScene/parsers/cameraParser.hpp"
#include "StarletScene/parsers/gridParser.hpp"
#include "StarletScene/parsers/textureParser.hpp"
#include "StarletScene/parsers/primitiveParser.hpp"

#include "StarletParsers/fileParser.hpp"
#include "StarletParsers/parserUtils.hpp"
#include "StarletParsers/utils/log.hpp"

#include <string>
#include <fstream>
#include <iomanip>

bool SceneLoader::loadScene(Scene& scene, const std::string& path) {
	std::string src{};
	if (!loadFile(src, path)) return error("SceneLoader", "loadScene", "Failed to load path: " + path);

	const unsigned char* p = reinterpret_cast<const unsigned char*>(src.c_str());
	while (*p) {
		const unsigned char* nextLine = skipToNextLine(p);
		const unsigned char* endLine = trimEOL(p, nextLine);

		if (endLine <= p) {
			p = nextLine;
			continue;
		}

		if (!processSceneLine(scene, p)) {
			const std::size_t maxLen = 256;
			std::size_t len = static_cast<std::size_t>(endLine - p);
			if (len > maxLen) len = maxLen;
			std::string errorMsg;
			errorMsg.reserve(len);
			errorMsg.append(reinterpret_cast<const char*>(p), len);
			return error("SceneManager", "loadTxtScene", std::string("Failed to process scene line: \"") + errorMsg + "\"");
		}

		if (p < nextLine) p = nextLine;
	}
	return true;
}

bool SceneLoader::processSceneLine(Scene& scene, const unsigned char*& p) {
	if (!p || *p == '\0') return true;

	unsigned char token[64]{};
	parseToken(p, token, sizeof(token));

	const char* nameStr = reinterpret_cast<const char*>(token);
	if (!p || strlen(nameStr) == 0) return true;
	if (strcmp(nameStr, "comment") == 0 || nameStr[0] == '#') {
		p = skipToNextLine(p);
		return true;
	}

	StarEntity entity = scene.createEntity();
	bool handled{ false };
	if (strcmp(nameStr, "model") == 0)            handled = parseAndAddObject<Model>(scene, p, &parseModel, entity);
	else if (strcmp(nameStr, "light") == 0)       handled = parseAndAddObject<Light>(scene, p, &parseLight, entity);
	else if (strcmp(nameStr, "camera") == 0)      handled = parseAndAddObject<Camera>(scene, p, &parseCamera, entity);
	else if (strcmp(nameStr, "texture") == 0)     handled = parseAndAddObject<TextureData>(scene, p, &parseTexture, entity);
	else if (strcmp(nameStr, "textureCube") == 0) handled = parseAndAddObject<TextureData>(scene, p, &parseCubeTexture, entity);
	else if (strcmp(nameStr, "textureAdd") == 0)  handled = parseAndAddObject<TextureConnection>(scene, p, &parseTextureConnection, entity);
	else if (strcmp(nameStr, "triangle") == 0)    handled = parseAndAddObject<Primitive>(scene, p, &parseTriangle, entity);
	else if (strcmp(nameStr, "square") == 0)      handled = parseAndAddObject<Primitive>(scene, p, &parseSquare, entity);
	else if (strcmp(nameStr, "cube") == 0)        handled = parseAndAddObject<Primitive>(scene, p, &parseCube, entity);
	else if (strcmp(nameStr, "squareGrid") == 0)  handled = parseAndAddObject<Grid>(scene, p, &parseSquareGrid, entity);
	else if (strcmp(nameStr, "cubeGrid") == 0)    handled = parseAndAddObject<Grid>(scene, p, &parseCubeGrid, entity);
	return handled ? true : error("SceneManager", "processSceneLine", "Failed to handle: " + std::string(nameStr));
}

bool SceneLoader::saveScene(const Scene& scene) {
	std::ofstream file(scene.getScenePath());
	if (!file.is_open()) return error("SceneManager", "saveTxtScene", "Failed to open scene file for saving: " + scene.getScenePath());
	file << std::fixed << std::setprecision(3);

	file << "comment, name, pos(xyz), rot(yaw pitch), fov, nearPlane farPlane, camSpeed\n";
	for (const Camera* cam : scene.getComponentsOfType<Camera>()) {
		file << "camera, "
				 << cam->name << ", "
				 << cam->pos << ", "
				 << cam->yaw << " " << cam->pitch << ", "
				 << cam->fov << ", "
				 << cam->nearPlane << " " << cam->farPlane << ", "
				 << cam->moveSpeed << "\n";
	}

	file << "\ncomment, name, meshPath, pos(xyz), rot(xyz), scale(xyz), colour(Int, Named Coloured, Random, Rainbow, PLY), specular(rgb, power)\n";
	for (const Model* model : scene.getComponentsOfType<Model>()) {
		if (model->name.rfind("triangle_instance", 0) == 0 || model->name.rfind("cube_instance_", 0) == 0 || model->name.rfind("square_instance_", 0) == 0)
			continue;

		file << "model, "
			<< model->name << ", "
			<< model->meshPath << ", "
			<< model->transform.pos << ", "
			<< model->transform.rot << ", "
			<< model->transform.size << ", ";

		switch (model->colourMode) {
		case ColourMode::Solid: {
			Vec4 rgba { model->colour.x * 255.0f, model->colour.y * 255.0f, model->colour.z * 255.0f, model->colour.w * 255.0f };
			if      (rgba.r == 255 && rgba.g == 0 && rgba.b == 0 && rgba.a == 255) file << "Red";
			else if (rgba.r == 0 && rgba.g == 255 && rgba.b == 0 && rgba.a == 255) file << "Green";
			else if (rgba.r == 0 && rgba.g == 0 && rgba.b == 255 && rgba.a == 255) file << "Blue";
			else file << rgba;
			break;
		}
		case ColourMode::Random:           file << "Random"; break;
		case ColourMode::VerticalGradient: file << "Rainbow"; break;
		case ColourMode::PLYColour:        file << "PLY"; break;
		default: break;
		}

		file << ", " << model->specular << "\n";
	}

	file << "\ncomment, name, type, pos (xyz), diffuse (rgba), attention (xyzw), direction, param1 (spotlight inner, spotlight outer), param2 (on/off)\n";
	for (const Light* light : scene.getComponentsOfType<Light>()) {
		if (!light->enabled) continue;

		const std::string camType =
			(light->param1.x == 0) ? "Point" :
			(light->param1.x == 1) ? "Spot" :
			/*      param1.x == 2)*/ "Directional";

		file << "light, "
			<< light->name << ", "
			<< camType << ", "
			<< light->pos << ", "
			<< light->diffuse << ", "
			<< light->attenuation << ", "
			<< light->direction << ", "
			<< light->param1.y << "\n";
	}

	return true;
}