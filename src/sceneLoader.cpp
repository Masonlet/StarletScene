#include "StarletScene/scene.hpp"
#include "StarletScene/sceneLoader.hpp"

#include "StarletScene/components/model.hpp"
#include "StarletScene/components/light.hpp"
#include "StarletScene/components/camera.hpp"
#include "StarletScene/components/grid.hpp"
#include "StarletScene/components/textureData.hpp"
#include "StarletScene/components/textureConnection.hpp"
#include "StarletScene/components/primitive.hpp"
#include "StarletScene/components/transform.hpp"
#include "StarletScene/components/velocity.hpp"

#include "StarletScene/parsers/modelParser.hpp"
#include "StarletScene/parsers/lightParser.hpp"
#include "StarletScene/parsers/cameraParser.hpp"
#include "StarletScene/parsers/gridParser.hpp"
#include "StarletScene/parsers/textureParser.hpp"
#include "StarletScene/parsers/primitiveParser.hpp"
#include "StarletScene/parsers/velocityParser.hpp"

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

	if (strcmp(nameStr, "model") == 0) {
		StarEntity entity = scene.createEntity();
		Model* model = scene.addComponent<Model>(entity);
		TransformComponent* transform = scene.addComponent<TransformComponent>(entity);
		return parseModel(p, *model, *transform);
	}
	else if (strcmp(nameStr, "light") == 0) {
		StarEntity entity = scene.createEntity();
		Light* light = scene.addComponent<Light>(entity);
		TransformComponent* transform = scene.addComponent<TransformComponent>(entity);
		return parseLight(p, *light, *transform);
	}
	else if (strcmp(nameStr, "camera") == 0) {
		StarEntity entity = scene.createEntity();
		Camera* camera = scene.addComponent<Camera>(entity);
		TransformComponent* transform = scene.addComponent<TransformComponent>(entity);
		return parseCamera(p, *camera, *transform);
	}
	else if (strcmp(nameStr, "texture") == 0) {
		StarEntity entity = scene.createEntity();
		return parseAndAddObject<TextureData>(scene, p, &parseTexture, entity);
	}
	else if (strcmp(nameStr, "textureCube") == 0) {
		StarEntity entity = scene.createEntity();
		return parseAndAddObject<TextureData>(scene, p, &parseCubeTexture, entity);
	}
	else if (strcmp(nameStr, "textureAdd") == 0) {
		StarEntity entity = scene.createEntity();
		return parseAndAddObject<TextureConnection>(scene, p, &parseTextureConnection, entity);
	}
	else if (strcmp(nameStr, "triangle") == 0) {
		StarEntity entity = scene.createEntity();
		Primitive* primitive = scene.addComponent<Primitive>(entity);
		TransformComponent* transform = scene.addComponent <TransformComponent>(entity);
		return parseTriangle(p, *primitive, *transform);
	}
	else if (strcmp(nameStr, "square") == 0) {
		StarEntity entity = scene.createEntity();
		Primitive* primitive = scene.addComponent<Primitive>(entity);
		TransformComponent* transform = scene.addComponent<TransformComponent>(entity);
		return parseSquare(p, *primitive, *transform);
	}
	else if (strcmp(nameStr, "cube") == 0) {
		StarEntity entity = scene.createEntity();
		Primitive* primitive = scene.addComponent<Primitive>(entity);
		TransformComponent* transform = scene.addComponent<TransformComponent>(entity);
		return parseSquare(p, *primitive, *transform);
	}
	else if (strcmp(nameStr, "squareGrid") == 0) {
		StarEntity entity = scene.createEntity();
		Grid* grid = scene.addComponent<Grid>(entity);
		TransformComponent* transform = scene.addComponent<TransformComponent>(entity);
		return parseSquareGrid(p, *grid, *transform);
	}
	else if (strcmp(nameStr, "cubeGrid") == 0) {
		StarEntity entity = scene.createEntity();
		Grid* grid = scene.addComponent<Grid>(entity);
		TransformComponent* transform = scene.addComponent<TransformComponent>(entity);
		return parseCubeGrid(p, *grid, *transform);
	}
	else if (strcmp(nameStr, "velocity") == 0) {
		unsigned char nameToken[256]{};
		parseToken(p, nameToken, sizeof(nameToken));
		const std::string entityName = reinterpret_cast<const char*>(nameToken);

		StarEntity entity = scene.getEntityByName<Model>(entityName);
		if (entity != -1) {
			VelocityComponent* velocity = scene.addComponent<VelocityComponent>(entity);
			if (velocity) return parseVelocity(p, *velocity);
			else return error("SceneLoader", "processSceneLine", "Failed to add VelocityComponent to entity " + entityName);
		}
		
	}

	return error("SceneManager", "processSceneLine", "Failed to handle: " + std::string(nameStr));
}

bool SceneLoader::saveScene(const Scene& scene) {
	std::ofstream file(scene.getScenePath());
	if (!file.is_open()) return error("SceneManager", "saveTxtScene", "Failed to open scene file for saving: " + scene.getScenePath());
	file << std::fixed << std::setprecision(3);

	file << "comment, name, pos(xyz), rot(yaw pitch), fov, nearPlane farPlane, camSpeed\n";
	for (const auto& pair : scene.getEntitiesOfType<Camera>()) {
		const StarEntity entity = pair.first;
		const Camera* cam = pair.second;

		if (!scene.hasComponent<TransformComponent>(entity)) continue;
		const TransformComponent& transform = scene.getComponent<TransformComponent>(entity);

		file << "camera, "
			   << cam->name << ", "
			   << transform.pos << ", "
				 << transform.rot.x << " " << transform.rot.y << ", "
				 << cam->fov << ", "
				 << cam->nearPlane << " " << cam->farPlane << ", "
				 << cam->moveSpeed << "\n";
	}

	file << "\ncomment, name, meshPath, pos(xyz), rot(xyz), scale(xyz), colour(Int, Named Colour, Random, Rainbow, PLY), specular(rgb, power)\n";
	for (const auto& pair : scene.getEntitiesOfType<Model>()) {
		const StarEntity entity = pair.first;
		const Model* model = pair.second;
		
		if (model->name.rfind("triangle_instance", 0) == 0 || model->name.rfind("cube_instance_", 0) == 0 || model->name.rfind("square_instance_", 0) == 0)
			continue;

		if (!scene.hasComponent<TransformComponent>(entity)) continue;
		const TransformComponent& transform = scene.getComponent<TransformComponent>(entity);

		file << "model, "
			<< model->name << ", "
			<< model->meshPath << ", "
			<< transform.pos << ", "
			<< transform.rot << ", "
			<< transform.size << ", ";

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
	for (const auto& pair : scene.getEntitiesOfType<Light>()) {
		const StarEntity entity = pair.first;
		const Light* light = pair.second;

		if (!scene.hasComponent<TransformComponent>(entity)) continue;
		const TransformComponent& transform = scene.getComponent<TransformComponent>(entity);

		if (!light->enabled) continue;

		const std::string camType =
			(light->param1.x == 0) ? "Point" :
			(light->param1.x == 1) ? "Spot" :
			/*      param1.x == 2)*/ "Directional";

		file << "light, "
			<< light->name << ", "
			<< camType << ", "
			<< transform.pos << ", "
			<< light->diffuse << ", "
			<< light->attenuation << ", "
			<< transform.rot << ", "
			<< light->param1.y << "\n";
	}

	return true;
}