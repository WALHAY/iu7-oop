#pragma once

#include <list>
#include <objects/Object.hpp>

class Composite : public Object
{
  public:
    void add(std::shared_ptr<Object> object) override;
    void remove(iterator &iter) override;

    iterator begin() override;
    iterator end() override;

    bool isComposite() override;
    void accept(std::shared_ptr<ObjectVisitor> visitor) override;

  private:
    std::list<std::shared_ptr<Object>> stored;
};
