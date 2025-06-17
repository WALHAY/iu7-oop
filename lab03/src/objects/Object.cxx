#include <objects/Object.hpp>
#include <exceptions/NotImplementedException.hpp>

Object::Object() : objectId(Object::lastId++)
{
}

auto Object::id() -> id_type
{
    return objectId;
}

void Object::add(std::shared_ptr<Object> object)
{
    throw NotImplementedException(__FILE_NAME__, __FUNCTION__, __LINE__);
}

void Object::remove(iterator &iter)
{
    throw NotImplementedException(__FILE_NAME__, __FUNCTION__, __LINE__);
}

auto Object::begin() -> iterator
{
    throw NotImplementedException(__FILE_NAME__, __FUNCTION__, __LINE__);
}

auto Object::end() -> iterator
{
    throw NotImplementedException(__FILE_NAME__, __FUNCTION__, __LINE__);
}

bool Object::isComposite()
{
    return false;
}

bool Object::isCamera()
{
    return false;
}
