#include <scene/loader/directors/SceneDirector.hpp>
#include <QDebug>

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
			qDebug() << "Build camera" << cameraPath->string();
            builder->buildCamera(*cameraPath);
		}

        if (modelPath)
		{
			qDebug() << "Build model" << modelPath->string();
            builder->buildModel(*modelPath);
		}
    }

	return builder->get();
}
