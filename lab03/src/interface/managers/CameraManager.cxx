#include <interface/managers/CameraManager.hpp>

// CameraManager::CameraManager() {
//
// }

std::shared_ptr<Camera> CameraManager::getActiveCamera()
{
    return activeCamera;
}

void CameraManager::setActiveCamera(Object::id_type id)
{
    auto scene = sceneManager->getScene();
    auto find = std::ranges::find_if(scene->begin(), scene->end(),
                                     [id](const auto &obj) { return obj->isCamera() && obj->id() == id; });

    if (find == scene->end())
        this->activeCamera = nullptr;
    else
        this->activeCamera = std::static_pointer_cast<Camera>(*find);
}

void CameraManager::setSceneManager(std::shared_ptr<SceneManager> sceneManager)
{
    this->sceneManager = sceneManager;
}
