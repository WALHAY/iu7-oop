#pragma once

#include "interface/commands/BaseCommand.hpp"
class ChangeCameraCommand : public BaseCommand {
	using Action = void(CameraManager::*)(Object::id_type);
public:
	ChangeCameraCommand(Object::id_type id) : id(id) {}

	void execute() const override {
		((*cameraManager).*action)(id);
	}
private:
	Object::id_type id;

	Action action = &CameraManager::setActiveCamera;
};

