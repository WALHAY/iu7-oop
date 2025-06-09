#include <interface/commands/BaseCommand.hpp>

BaseCommand::~BaseCommand() = default;

bool BaseCommand::isComposite()
{
    return false;
}

void BaseCommand::add(std::shared_ptr<BaseCommand> command)
{
}

void BaseCommand::remove(iterator &iter)
{
}

auto BaseCommand::begin() const -> iterator
{
}

auto BaseCommand::end() const -> iterator
{
}

void BaseCommand::setManagers(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<DrawManager> drawManager,
                              std::shared_ptr<LoadManager> loadManager,
                              std::shared_ptr<SelectionManager> selectionManager,
                              std::shared_ptr<CameraManager> cameraManager, std::shared_ptr<TransformManager> transformManager)
{
    this->sceneManager = sceneManager;
    this->drawManager = drawManager;
    this->loadManager = loadManager;
    this->selectionManager = selectionManager;
    this->cameraManager = cameraManager;
	this->transformManager = transformManager;
}
