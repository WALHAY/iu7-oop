#include <objects/Composite.hpp>
#include <visitors/ObjectVisitor.hpp>

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
	if(object.get() != this)
    	stored.push_back(object);
}

void Composite::remove(iterator &iter)
{
    stored.erase(iter);
}

void Composite::accept(std::shared_ptr<ObjectVisitor> visitor)
{
	for(auto &object : *this)
		object->accept(visitor);
}
