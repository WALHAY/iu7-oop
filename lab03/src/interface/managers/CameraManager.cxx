#include <interface/managers/CameraManager.hpp>

std::shared_ptr<Camera> CameraManager::getActiveCamera()
{
    return activeCamera;
}

void CameraManager::setActiveCamera(std::shared_ptr<Scene> scene, Object::id_type id)
{
    if (scene == nullptr)
        return;

    auto find = std::ranges::find_if(scene->begin(), scene->end(),
                                     [id](const auto &obj) { return obj->isCamera() && obj->id() == id; });

    if (find == scene->end())
        this->activeCamera = nullptr;
    else
        this->activeCamera = std::static_pointer_cast<Camera>(*find);
}
