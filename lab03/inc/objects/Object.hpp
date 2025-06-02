#pragma once

#include <list>
#include <memory>
#include <sys/_types/_id_t.h>

class ObjectVisitor;

class Object
{
  public:
    using id_type = id_t;
    using iterator = std::list<std::shared_ptr<Object>>::iterator;

    virtual ~Object();

    virtual id_type id();

    virtual void add(std::shared_ptr<Object> object);
    virtual void remove(iterator &iter);

    virtual iterator begin();
    virtual iterator end();

    virtual bool isComposite();
    virtual void accept(std::shared_ptr<ObjectVisitor> visitor) = 0;

  private:
    id_type _id;
};
