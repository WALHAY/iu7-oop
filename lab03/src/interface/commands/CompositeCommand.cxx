#include <interface/commands/CompositeCommand.hpp>

void CompositeCommand::add(std::shared_ptr<BaseCommand> command)
{
    if (command.get() == this)
        return;

    this->commands.push_back(command);
}

void CompositeCommand::remove(iterator &iter)
{
    this->commands.erase(iter);
}

auto CompositeCommand::begin() const -> iterator
{
    return this->commands.cbegin();
}

auto CompositeCommand::end() const -> iterator
{
    return this->commands.cend();
}

bool CompositeCommand::isComposite()
{
    return true;
}

void CompositeCommand::execute() const
{
    for (auto &obj : *this)
	{
		obj->setManagers(sceneManager, drawManager, loadManager, selectionManager, cameraManager, transformManager);
        obj->execute();
	}
}
