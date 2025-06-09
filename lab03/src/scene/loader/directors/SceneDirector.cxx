#include <QDebug>
#include <scene/loader/directors/SceneDirector.hpp>

SceneDirector::SceneDirector(std::shared_ptr<BaseSceneBuilder> builder)
{
    this->builder = builder;
}

std::shared_ptr<Scene> SceneDirector::create(std::shared_ptr<BaseSceneStreamReader> reader)
{
    builder->build();

    std::optional<std::filesystem::path> cameraPath;
    std::optional<std::filesystem::path> modelPath;
    while ((cameraPath = reader->getCameraPath()) || (modelPath = reader->getModelPath()))
    {
        if (cameraPath)
        {
            builder->buildCamera(*cameraPath);
            continue;
        }

        if (modelPath)
		{
            builder->buildModel(*modelPath);
			continue;
		}
    }

    return builder->get();
}
