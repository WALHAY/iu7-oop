#include <interface/managers/SelectionManager.hpp>

void SelectionManager::setSceneManager(std::shared_ptr<SceneManager> sceneManager)
{
    this->sceneManager = sceneManager;
}

void SelectionManager::add(id_type id)
{
    auto scene = sceneManager->getScene();

    auto find = std::ranges::find_if(scene->begin(), scene->end(), [id](const auto &obj) { return obj->id() == id; });

    composite->add(*find);
}

void SelectionManager::remove(id_type id)
{
    auto find =
        std::ranges::find_if(composite->begin(), composite->end(), [id](const auto &obj) { return obj->id() == id; });

    composite->remove(find);
}

std::shared_ptr<Composite> SelectionManager::getSelection()
{
    return composite;
}
