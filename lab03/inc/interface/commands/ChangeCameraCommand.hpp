#pragma once

#include "interface/commands/BaseCommand.hpp"

class ChangeCameraCommand : public BaseCommand {
	using Action = void(CameraManager::*)(std::shared_ptr<Scene>, Object::id_type);
public:
	ChangeCameraCommand(Object::id_type id) : id(id) {}

	void execute() const override {
		((*cameraManager).*action)(sceneManager->getScene(), id);
	}
private:
	Object::id_type id;

	Action action = &CameraManager::setActiveCamera;
};

