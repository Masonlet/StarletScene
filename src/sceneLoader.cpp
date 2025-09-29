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

#include "StarletParser/parser.hpp"
#include "StarletParser/utils/log.hpp"

#include <string>
#include <fstream>
#include <iomanip>

bool SceneLoader::loadScene(Scene& scene, const std::string& path) {
	Parser parser;
	return parser.parseScene(scene, path)
		? debugLog("SceneLoader", "loadScene", "Loaded: " + path)
		: error("SceneLoader", "loadScene", "Failed to load: " + path);
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