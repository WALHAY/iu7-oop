#include <QDebug>
#include <scene/Scene.hpp>

void Scene::add(std::shared_ptr<Object> object)
{
    if (object == nullptr)
        return;

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
