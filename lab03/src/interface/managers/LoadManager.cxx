#include "wireframe/loader/BaseBuilder.hpp"
#include "wireframe/loader/BaseDirector.hpp"
#include "wireframe/loader/builders/ModelBuilder.hpp"
#include "wireframe/loader/directors/ModelDirector.hpp"
#include "wireframe/loader/readers/TxtStreamReader.hpp"
#include <QDebug>
#include <filesystem>
#include <fstream>
#include <interface/managers/LoadManager.hpp>

void LoadManager::loadScene(std::filesystem::path &path)
{
    std::shared_ptr<std::ifstream> str = std::make_shared<std::ifstream>(path);
    std::shared_ptr<TxtStreamReader> reader = std::make_shared<TxtStreamReader>(str);
    std::shared_ptr<BaseBuilder> builder = std::make_shared<ModelBuilder>();
    std::shared_ptr<BaseDirector> director = std::make_shared<ModelDirector>(builder);

    auto scene = sceneManager->getScene();
    scene->add(director->create(reader));
}

void LoadManager::remove(Object::id_type id)
{
    if (sceneManager == nullptr)
        return;

    auto scene = sceneManager->getScene();

    if (scene == nullptr)
        return;

    auto find = std::ranges::find_if(scene->begin(), scene->end(), [id](const auto &a) { return a->id() == id; });

    scene->remove(find);
}

void LoadManager::setSceneManager(std::shared_ptr<SceneManager> sceneManager)
{
    this->sceneManager = sceneManager;
}
