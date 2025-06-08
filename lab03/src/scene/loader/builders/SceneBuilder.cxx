#include "camera/loader/readers/TxtCameraReader.hpp"
#include "wireframe/loader/readers/TxtModelReader.hpp"
#include <fstream>
#include <scene/loader/builders/SceneBuilder.hpp>
#include <wireframe/loader/BaseModelDirector.hpp>

SceneBuilder::SceneBuilder(std::shared_ptr<BaseModelDirector> modelDirector,
                           std::shared_ptr<BaseCameraDirector> cameraDirector)
    : modelDirector(modelDirector), cameraDirector(cameraDirector)
{
}

void SceneBuilder::build()
{
    this->scene = std::make_shared<Scene>();
}

void SceneBuilder::buildCamera(std::filesystem::path &cameraPath)
{
    if (scene == nullptr)
        throw std::exception();

    auto stream = std::make_shared<std::ifstream>(cameraPath);
    std::shared_ptr<BaseCameraStreamReader> reader = std::make_shared<TxtCameraReader>(stream);

    scene->add(cameraDirector->create(reader));
}

void SceneBuilder::buildModel(std::filesystem::path &modelPath)
{
    if (scene == nullptr)
        throw std::exception();

    auto stream = std::make_shared<std::ifstream>(modelPath);
    std::shared_ptr<BaseModelStreamReader> reader = std::make_shared<TxtModelReader>(stream);

    scene->add(modelDirector->create(reader));
}

std::shared_ptr<Scene> SceneBuilder::get()
{
    return scene;
}
