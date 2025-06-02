#pragma once

#include <list>
#include <memory>
#include <objects/Object.hpp>

class Scene
{
  public:
    using iterator = std::list<std::shared_ptr<Object>>::iterator;

    Scene();

    void add(std::shared_ptr<Object> object);
    void remove(iterator &iter);

    iterator begin();
    iterator end();

  private:
    std::list<std::shared_ptr<Object>> objects;
};
