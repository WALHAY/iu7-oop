#include <interface/managers/SelectionManager.hpp>

SelectionManager::SelectionManager()
{
    this->composite = std::make_shared<Composite>();
}

void SelectionManager::add(std::shared_ptr<Scene> scene, id_type id)
{
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

    if (find != composite->end())
        composite->remove(find);
}

std::shared_ptr<Composite> SelectionManager::getSelection()
{
    return composite;
}
