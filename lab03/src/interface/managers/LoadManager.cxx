#include "camera/loader/BaseCameraBuilder.hpp"
#include "camera/loader/BaseCameraDirector.hpp"
#include "camera/loader/BaseCameraStreamReader.hpp"
#include "camera/loader/builders/CameraBuilder.hpp"
#include "camera/loader/directors/CameraDirector.hpp"
#include "camera/loader/readers/TxtCameraReader.hpp"
#include "interface/managers/ManagersExceptions.hpp"
#include "scene/loader/SceneDirector.hpp"
#include "scene/loader/SceneReader.hpp"
#include "stream/BaseStreamLoader.hpp"
#include "stream/StreamFileLoader.hpp"
#include "stream/TxtFileLoader.hpp"
#include "wireframe/loader/BaseModelBuilder.hpp"
#include "wireframe/loader/builders/ModelBuilder.hpp"
#include "wireframe/loader/directors/ModelDirector.hpp"
#include "wireframe/loader/readers/TxtModelReader.hpp"
#include <QDebug>
#include <filesystem>
#include <fstream>
#include <interface/managers/LoadManager.hpp>

void LoadManager::loadScene(std::filesystem::path path, callback_type callback = nullptr)
{
    if (!sceneManager)
        throw SceneManagerNotSetException(__FILE_NAME__, __FUNCTION__, __LINE__);

    std::shared_ptr<std::ifstream> str = std::make_shared<std::ifstream>(path);

    std::shared_ptr<BaseFileLoader> fileLoader = std::make_shared<TxtFileLoader>(path);
    std::shared_ptr<BaseStreamLoader> streamLoader = std::make_shared<StreamFileLoader>(fileLoader);

    std::shared_ptr<BaseModelStreamReader> modelStreamReader =
        std::make_shared<TxtModelReader>(streamLoader->getStream());
    std::shared_ptr<BaseCameraStreamReader> cameraStreamReader =
        std::make_shared<TxtCameraReader>(streamLoader->getStream());
    std::shared_ptr<BaseSceneStreamReader> sceneStreamReader = std::make_shared<SceneReader>(streamLoader->getStream());

    std::shared_ptr<BaseModelBuilder> modelBuilder = std::make_shared<ModelBuilder>();
    std::shared_ptr<BaseCameraBuilder> cameraBuilder = std::make_shared<CameraBuilder>();
    std::shared_ptr<BaseModelDirector> modelDirector = std::make_shared<ModelDirector>(modelBuilder, modelStreamReader);
    std::shared_ptr<BaseCameraDirector> cameraDirector =
        std::make_shared<CameraDirector>(cameraBuilder, cameraStreamReader);

    std::shared_ptr<SceneDirector> sceneLoader =
        std::make_shared<SceneDirector>(modelDirector, cameraDirector, sceneStreamReader);

    sceneLoader->setCallback(callback);

    sceneManager->setScene(sceneLoader->create());
}

void LoadManager::remove(std::shared_ptr<Scene> scene, Object::id_type id)
{
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
