#include <scene/loader/SceneDirector.hpp>

SceneDirector::SceneDirector(std::shared_ptr<BaseModelDirector> modelDirector,
                             std::shared_ptr<BaseCameraDirector> cameraDirector,
                             std::shared_ptr<BaseSceneStreamReader> sceneReader)
    : modelDirector(modelDirector), cameraDirector(cameraDirector), sceneReader(sceneReader)
{
}

void SceneDirector::setCallback(callback_type callback)
{
    this->callback = callback;
}

std::shared_ptr<Scene> SceneDirector::create()
{
    auto scene = std::make_shared<Scene>();

	bool failure = false;

    std::optional<ObjectType> type;
    while ((type = sceneReader->getType()))
    {
        std::shared_ptr<Object> obj;
        switch (*type)
        {
        case ObjectType::CAMERA:
            obj = cameraDirector->create();
            break;
        case ObjectType::MODEl:
            obj = modelDirector->create();
            break;
        }

        if (obj != nullptr)
        {
            scene->add(obj);

            if (callback != nullptr)
                callback(*type, obj->id());
        } else{
			failure = true;
			break;
		}
    }

    return failure ? nullptr : scene;
}
