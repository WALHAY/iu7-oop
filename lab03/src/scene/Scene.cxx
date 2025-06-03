#include <scene/Scene.hpp>

Scene::Scene()
{
}

void Scene::add(std::shared_ptr<Object> object)
{
    objects.push_back(object);
}

void Scene::remove(iterator &iter)
{
    objects.erase(iter);
}

auto Scene::begin() -> iterator
{
    return objects.begin();
}

auto Scene::end() -> iterator
{
    return objects.end();
}
