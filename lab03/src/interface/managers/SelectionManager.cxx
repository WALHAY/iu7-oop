#include <interface/managers/SelectionManager.hpp>

SelectionManager::SelectionManager()
{
	this->composite = std::make_shared<Composite>();
}

void SelectionManager::setSceneManager(std::shared_ptr<SceneManager> sceneManager)
{
    this->sceneManager = sceneManager;
}

void SelectionManager::add(id_type id)
{
    auto scene = sceneManager->getScene();

    if (scene == nullptr)
        return;

    auto find = std::ranges::find_if(scene->begin(), scene->end(), [id](const auto &obj) { return obj->id() == id; });

    if (find != scene->end())
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
