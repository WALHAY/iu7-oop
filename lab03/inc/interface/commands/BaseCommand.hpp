#pragma once

#include "interface/managers/CameraManager.hpp"
#include "interface/managers/LoadManager.hpp"
#include "interface/managers/SelectionManager.hpp"
#include <interface/managers/DrawManager.hpp>
#include <interface/managers/SceneManager.hpp>
#include <memory>

class BaseCommand
{
  public:
    using iterator = std::list<std::shared_ptr<BaseCommand>>::const_iterator;

    virtual ~BaseCommand() = 0;
    virtual void execute() const = 0;

    virtual void add(std::shared_ptr<BaseCommand> command);
    virtual void remove(iterator &iter);

    virtual iterator begin() const;
    virtual iterator end() const;

	virtual bool isComposite();

    virtual void setManagers(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<DrawManager> drawManager,
                             std::shared_ptr<LoadManager> loadManager,
                             std::shared_ptr<SelectionManager> selectionManager,
                             std::shared_ptr<CameraManager> cameraManager);

  protected:
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<DrawManager> drawManager;
    std::shared_ptr<LoadManager> loadManager;
    std::shared_ptr<SelectionManager> selectionManager;
    std::shared_ptr<CameraManager> cameraManager;
};
