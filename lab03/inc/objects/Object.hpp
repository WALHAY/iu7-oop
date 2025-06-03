#pragma once

#include <list>
#include <memory>

class ObjectVisitor;

class Object
{
  public:
    using id_type = int;
    using iterator = std::list<std::shared_ptr<Object>>::iterator;

	Object();
    virtual ~Object() = default;

    virtual id_type id();

    virtual void add(std::shared_ptr<Object> object);
    virtual void remove(iterator &iter);

    virtual iterator begin();
    virtual iterator end();

    virtual bool isComposite();
    virtual void accept(std::shared_ptr<ObjectVisitor> visitor) = 0;

  private:
    id_type objectId;
	static inline id_type lastId = 0;
};
