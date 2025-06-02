#include <objects/ObjectException.hpp>
#include <objects/Object.hpp>

auto Object::id() -> id_type {
	return _id;
}

void Object::add(std::shared_ptr<Object> object)
{
    throw NotImplemented(__FILE_NAME__, __FUNCTION__, __LINE__);
}

void Object::remove(iterator &iter)
{
    throw NotImplemented(__FILE_NAME__, __FUNCTION__, __LINE__);
}

auto Object::begin() -> iterator {
    throw NotImplemented(__FILE_NAME__, __FUNCTION__, __LINE__);
}

auto Object::end() -> iterator {
    throw NotImplemented(__FILE_NAME__, __FUNCTION__, __LINE__);
}

bool Object::isComposite() {
	return false;
}
