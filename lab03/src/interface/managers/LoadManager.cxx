#include "camera/loader/BaseCameraBuilder.hpp"
#include "camera/loader/BaseCameraDirector.hpp"
#include "camera/loader/builders/CameraBuilder.hpp"
#include "camera/loader/directors/CameraDirector.hpp"
#include "scene/loader/BaseSceneStreamReader.hpp"
#include "scene/loader/builders/SceneBuilder.hpp"
#include "scene/loader/directors/SceneDirector.hpp"
#include "scene/loader/readers/TxtSceneReader.hpp"
#include "wireframe/loader/BaseModelBuilder.hpp"
#include "wireframe/loader/builders/ModelBuilder.hpp"
#include "wireframe/loader/directors/ModelDirector.hpp"
#include <QDebug>
#include <filesystem>
#include <fstream>
#include <interface/managers/LoadManager.hpp>

void LoadManager::loadScene(std::filesystem::path path, std::function<void(ObjectType, Object::id_type)> callback)
{
    std::shared_ptr<std::ifstream> str = std::make_shared<std::ifstream>(path);
    std::shared_ptr<BaseSceneStreamReader> reader = std::make_shared<TxtSceneReader>(str);

    std::shared_ptr<BaseModelBuilder> modelBuilder = std::make_shared<ModelBuilder>();
    std::shared_ptr<BaseCameraBuilder> cameraBuilder = std::make_shared<CameraBuilder>();
    std::shared_ptr<BaseModelDirector> modelDirector = std::make_shared<ModelDirector>(modelBuilder);
    std::shared_ptr<BaseCameraDirector> cameraDirector = std::make_shared<CameraDirector>(cameraBuilder);

    auto sceneBuilder = std::make_shared<SceneBuilder>(modelDirector, cameraDirector);
    auto director = std::make_shared<SceneDirector>(sceneBuilder);

    auto scene = director->create(reader);
    sceneManager->setScene(scene);

    if (callback == nullptr)
        return;

    for (const auto &obj : *scene)
    {
        callback(obj->isCamera() ? ObjectType::CAMERA : ObjectType::MODEl, obj->id());
    }
}

void LoadManager::remove(Object::id_type id)
{
    if (sceneManager == nullptr)
        return;

    auto scene = sceneManager->getScene();

    if (scene == nullptr)
        return;

    auto find = std::ranges::find_if(scene->begin(), scene->end(), [id](const auto &a) { return a->id() == id; });

    if (find != scene->end())
        scene->remove(find);
}

void LoadManager::setSceneManager(std::shared_ptr<SceneManager> sceneManager)
{
    this->sceneManager = sceneManager;
}
