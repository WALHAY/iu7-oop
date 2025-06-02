#include <objects/Composite.hpp>
#include <visitor/ObjectVisitor.hpp>

bool Composite::isComposite()
{
    return true;
}

auto Composite::begin() -> iterator
{
    return stored.begin();
}

auto Composite::end() -> iterator
{
    return stored.end();
}

void Composite::add(std::shared_ptr<Object> object)
{
    stored.push_back(object);
}

void Composite::remove(iterator &iter)
{
    stored.erase(iter);
}

void Composite::accept(std::shared_ptr<ObjectVisitor> visitor)
{
	visitor->visit(*this);
}
