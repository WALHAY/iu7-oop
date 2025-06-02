#include <interface/Facade.hpp>

Facade::Facade()
{
	sceneManager = std::make_shared<SceneManager>();
}
