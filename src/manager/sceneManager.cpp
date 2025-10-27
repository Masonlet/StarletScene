#include "StarletScene/manager/sceneManager.hpp"
#include "StarletSerializer/utils/log.hpp"

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

namespace Starlet::Scene {
  bool SceneManager::loadTxtScene(const std::string& path) {
    Serializer::debugLog("SceneManager", "loadTxtScene", "Started: " + path);

    Serializer::SceneParser parser;
    Serializer::SceneData data;
    if (!parser.parse(basePath + path, data)) 
      return Serializer::error("SceneManager", "loadTxtScene", "Failed to load scene file");

    if (!loadScene(data))
      return Serializer::error("SceneManager", "loadTxtScene", "Failed to load scene");

    scene.setScenePath(basePath + path);
    return Serializer::debugLog("SceneManager", "loadTxtScene", "Finished: " + path);
  }

  bool SceneManager::saveTxtScene() {
    Serializer::debugLog("SceneManager", "saveTxtScene", "Started: " + scene.getScenePath());

    Serializer::Writer w;
    if (!w.writeScene(scene))
      return Serializer::error("SceneManager", "saveTxtScene", "Failed to save scene: " + basePath);

    return Serializer::debugLog("SceneManager", "saveTxtScene", "Finished: " + scene.getScenePath());
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
}

