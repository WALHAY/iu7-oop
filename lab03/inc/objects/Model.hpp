#pragma once

#include <objects/Object.hpp>
#include <wireframe/Wireframe.hpp>

class Model : public Object
{
  public:
    virtual ~Model();

	void accept(std::shared_ptr<ObjectVisitor> visitor) override = 0;
};
