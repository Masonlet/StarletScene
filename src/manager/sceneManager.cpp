#include "StarletScene/manager/sceneManager.hpp"
#include "StarletLogger/logger.hpp"

#include "StarletScene/component/model.hpp"
#include "StarletScene/component/light.hpp"
#include "StarletScene/component/camera.hpp"
#include "StarletScene/component/primitive.hpp"
#include "StarletScene/component/grid.hpp"
#include "StarletScene/component/textureData.hpp"
#include "StarletScene/component/transform.hpp"
#include "StarletScene/component/colour.hpp"
#include "StarletScene/component/velocity.hpp"

#include"StarletSerializer/parser/sceneParser.hpp"
#include "StarletSerializer/writer/writer.hpp"
#include "StarletSerializer/data/sceneData.hpp"

namespace Starlet::Scene {
  bool SceneManager::loadTxtScene(const std::string& path) {
    Logger::debugLog("SceneManager", "loadTxtScene", "Started: " + path);

    Serializer::SceneParser parser;
    Serializer::SceneData data;
    if (!parser.parse(basePath + path, data)) 
      return Logger::error("SceneManager", "loadTxtScene", "Failed to load scene file");

    if (!loadScene(data))
      return Logger::error("SceneManager", "loadTxtScene", "Failed to load scene");

    scene.setScenePath(basePath + path);
    return Logger::debugLog("SceneManager", "loadTxtScene", "Finished: " + path);
  }

  bool SceneManager::saveTxtScene() {
    Logger::debugLog("SceneManager", "saveTxtScene", "Started: " + scene.getScenePath());

    Serializer::SceneData data;
    if (!saveScene(data))
      return Logger::error("SceneManager", "saveTxtScene", "Failed to save scene data");

    Serializer::Writer w;
    if (!w.writeScene(data, scene.getScenePath()))
      return Logger::error("SceneManager", "saveTxtScene", "Failed to save scene: " + scene.getScenePath());

    return Logger::debugLog("SceneManager", "saveTxtScene", "Finished: " + scene.getScenePath());
  }

  bool SceneManager::loadScene(Serializer::SceneData& data) {
    for (Serializer::ModelData& modelData : data.models) {
      Entity entity = scene.createEntity();
      Model* model = scene.addComponent<Model>(entity);
      TransformComponent* transform = scene.addComponent<TransformComponent>(entity);
      ColourComponent* colour = scene.addComponent<ColourComponent>(entity);

      model->name = modelData.name;
      model->meshPath = modelData.meshPath;
      model->isLighted = modelData.isLighted;
      model->isVisible = modelData.isVisible;
      model->useTextures = modelData.useTextures;
      model->mode = static_cast<ColourMode>(modelData.mode);
      model->textureTiling = modelData.textureTiling;
      for (int i = 0; i < Model::NUM_TEXTURES; ++i) {
        model->textureNames[i] = modelData.textureNames[i];
        model->textureMixRatio[i] = modelData.textureMixRatio[i];
      }

      transform->pos = modelData.transform.pos;
      transform->rot = modelData.transform.rot;
      transform->size = modelData.transform.size;

      colour->colour = modelData.colour.colour;
      colour->specular = modelData.colour.specular;
    }

    for (Serializer::LightData& lightData : data.lights) {
      Entity entity = scene.createEntity();
      Light* light = scene.addComponent<Light>(entity);
      TransformComponent* transform = scene.addComponent<TransformComponent>(entity);
      ColourComponent* colour = scene.addComponent<ColourComponent>(entity);

      light->name = lightData.name;
      light->enabled = lightData.enabled;
      light->type = static_cast<LightType>(lightData.type);
      light->attenuation = lightData.attenuation;
      light->param1 = lightData.param1;

      transform->pos = lightData.transform.pos;
      transform->rot = lightData.transform.rot;
      transform->size = lightData.transform.size;

      colour->colour = lightData.colour.colour;
      colour->specular = lightData.colour.specular;
    }

    for (Serializer::CameraData& cameraData : data.cameras) {
      Entity entity = scene.createEntity();
      Camera* camera = scene.addComponent<Camera>(entity);
      TransformComponent* transform = scene.addComponent<TransformComponent>(entity);

      camera->name = cameraData.name;
      camera->moveSpeed = cameraData.moveSpeed;
      camera->mouseSpeed = cameraData.mouseSpeed;
      camera->fov = cameraData.fov;
      camera->nearPlane = cameraData.nearPlane;
      camera->farPlane = cameraData.farPlane;
      camera->enabled = cameraData.enabled;
      camera->paused = cameraData.paused;

      transform->pos = cameraData.transform.pos;
      transform->rot = cameraData.transform.rot;
      transform->size = cameraData.transform.size;
    }

    for (Serializer::TextureData& textureData : data.textures) {
      Entity entity = scene.createEntity();
      TextureData* texture = scene.addComponent<TextureData>(entity);

      for (int i = 0; i < 6; ++i)
        texture->faces[i] = textureData.faces[i];

      texture->name = textureData.name;
      texture->mix = textureData.mix;
      texture->tiling = textureData.tiling;
      texture->isCube = textureData.isCube;
    }

    for (Serializer::TextureConnection& textureConnection : data.textureConnections) {
      Entity entity = scene.getEntityByName<Model>(textureConnection.modelName);
      if (entity != -1) {
        Model& model = scene.getComponent<Model>(entity);
        model.textureNames[textureConnection.slot] = textureConnection.textureName;
        model.textureMixRatio[textureConnection.slot] = textureConnection.mix;
        model.useTextures = true;
      }
    }

    for (Serializer::PrimitiveData& primitiveData : data.primitives) {
      Entity entity = scene.createEntity();
      Primitive* primitive = scene.addComponent<Primitive>(entity);
      TransformComponent* transform = scene.addComponent <TransformComponent>(entity);
      ColourComponent* colour = scene.addComponent<ColourComponent>(entity);

      primitive->name = primitiveData.name;
      primitive->type = static_cast<PrimitiveType>(primitiveData.type);

      transform->pos = primitiveData.transform.pos;
      transform->rot = primitiveData.transform.rot;
      transform->size = primitiveData.transform.size;

      colour->colour = primitiveData.colour.colour;
      colour->specular = primitiveData.colour.specular;
    }

    for (Serializer::GridData& gridData : data.grids) {
      Entity entity = scene.createEntity();
      Grid* grid = scene.addComponent<Grid>(entity);
      TransformComponent* transform = scene.addComponent<TransformComponent>(entity);
      ColourComponent* colour = scene.addComponent<ColourComponent>(entity);

      grid->name = gridData.name;
      grid->type = static_cast<GridType>(gridData.type);
      grid->count = gridData.count;
      grid->spacing = gridData.spacing;

      transform->pos = gridData.transform.pos;
      transform->rot = gridData.transform.rot;
      transform->size = gridData.transform.size;

      colour->colour = gridData.colour.colour;
      colour->specular = gridData.colour.specular;
    }

    for (Serializer::VelocityData& velocityData : data.velocities) {
      Entity entity = scene.getEntityByName<Model>(velocityData.modelName);
      if (entity != -1) {
        VelocityComponent* velocity = scene.addComponent<VelocityComponent>(entity);
        velocity->velocity = velocityData.velocity;
      }
    }

    scene.setAmbientLight({ data.ambientLight, 1.0f });
    return true;
  }

  bool SceneManager::saveScene(Serializer::SceneData& data) {
    for (const auto& [entity, model] : scene.getEntitiesOfType<Model>()) {
			Serializer::ModelData modelData;
			modelData.name = model->name;
			modelData.meshPath = model->meshPath;
			modelData.isLighted = model->isLighted;
			modelData.isVisible = model->isVisible;
			modelData.useTextures = model->useTextures;
			modelData.mode = static_cast<Serializer::ColourMode>(model->mode);
			modelData.textureTiling = model->textureTiling;
      for (int i = 0; i < Model::NUM_TEXTURES; ++i) {
        modelData.textureNames[i] = model->textureNames[i];
        modelData.textureMixRatio[i] = model->textureMixRatio[i];

        if (!model->textureNames[i].empty()) {
          Serializer::TextureConnection connection;
          connection.modelName = model->name;
          connection.textureName = model->textureNames[i];
          connection.slot = i;
          connection.mix = model->textureMixRatio[i];
          data.textureConnections.push_back(connection);
        }
      }

			const TransformComponent& transform = scene.getComponent<TransformComponent>(entity);
			modelData.transform.pos = transform.pos;
      modelData.transform.rot = transform.rot;
      modelData.transform.size = transform.size;

			const ColourComponent& colour = scene.getComponent<ColourComponent>(entity);
			modelData.colour.colour = colour.colour;
			modelData.colour.specular = colour.specular;

			data.models.push_back(modelData);
    }

    for (const auto& [entity, light] : scene.getEntitiesOfType<Light>()) {
			Serializer::LightData lightData;
			lightData.name = light->name;
			lightData.enabled = light->enabled;
			lightData.type = static_cast<Serializer::LightType>(light->type);
			lightData.attenuation = light->attenuation;
      lightData.param1 = light->param1;

			const TransformComponent& transform = scene.getComponent<TransformComponent>(entity);
      lightData.transform.pos = transform.pos;
      lightData.transform.rot = transform.rot;
			lightData.transform.size = transform.size;

			const ColourComponent& colour = scene.getComponent<ColourComponent>(entity);
			lightData.colour.colour = colour.colour;
			lightData.colour.specular = colour.specular;

			data.lights.push_back(lightData);
    }

    for (const auto& [entity, cam] : scene.getEntitiesOfType<Camera>()) {
			Serializer::CameraData cameraData;
      cameraData.name = cam->name;
			cameraData.moveSpeed = cam->moveSpeed;
			cameraData.mouseSpeed = cam->mouseSpeed;
			cameraData.fov = cam->fov;
			cameraData.nearPlane = cam->nearPlane;
			cameraData.farPlane = cam->farPlane;
			cameraData.enabled = cam->enabled;
			cameraData.paused = cam->paused;

      const TransformComponent& transform = scene.getComponent<TransformComponent>(entity);
			cameraData.transform.pos = transform.pos;
			cameraData.transform.rot = transform.rot;
      cameraData.transform.size = transform.size;

			data.cameras.push_back(cameraData);
    }

    for (const auto& [entity, texture] : scene.getEntitiesOfType<TextureData>()) {
      Serializer::TextureData textureData;
      textureData.name = texture->name;
      textureData.mix = texture->mix;
      textureData.tiling = texture->tiling;
      textureData.isCube = texture->isCube;
      for (int i = 0; i < 6; ++i)
        textureData.faces[i] = texture->faces[i];

      data.textures.push_back(textureData);
		}

    for (const auto& [entity, primitive] : scene.getEntitiesOfType<Primitive>()) {
      Serializer::PrimitiveData primitiveData;
      primitiveData.name = primitive->name;
      primitiveData.type = static_cast<Serializer::PrimitiveType>(primitive->type);

      const TransformComponent& transform = scene.getComponent<TransformComponent>(entity);
      primitiveData.transform.pos = transform.pos;
      primitiveData.transform.rot = transform.rot;
      primitiveData.transform.size = transform.size;

      const ColourComponent& colour = scene.getComponent<ColourComponent>(entity);
      primitiveData.colour.colour = colour.colour;
      primitiveData.colour.specular = colour.specular;
      data.primitives.push_back(primitiveData);
    }

    for (const auto& [entity, grid] : scene.getEntitiesOfType<Grid>()) {
      Serializer::GridData gridData;
      gridData.name = grid->name;
      gridData.type = static_cast<Serializer::GridType>(grid->type);
      gridData.count = grid->count;
      gridData.spacing = grid->spacing;

      const TransformComponent& transform = scene.getComponent<TransformComponent>(entity);
      gridData.transform.pos = transform.pos;
      gridData.transform.rot = transform.rot;
      gridData.transform.size = transform.size;

      const ColourComponent& colour = scene.getComponent<ColourComponent>(entity);
      gridData.colour.colour = colour.colour;
      gridData.colour.specular = colour.specular;

      data.grids.push_back(gridData);
    }

    for (const auto& [entity, velocity] : scene.getEntitiesOfType<VelocityComponent>()) {
      const Model& model = scene.getComponent<Model>(entity);

      Serializer::VelocityData velocityData;
      velocityData.modelName = model.name;
      velocityData.velocity = velocity->velocity;

      data.velocities.push_back(velocityData);
    }

		const Math::Vec4<float>& colour = scene.getAmbientLight();
    data.ambientLight = { colour.r, colour.g, colour.b };
    data.ambientEnabled = true;
		return true;
  }
}