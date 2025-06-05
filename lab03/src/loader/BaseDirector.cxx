#include "loader/BaseBuilder.hpp"
#include <loader/BaseDirector.hpp>

BaseDirector::~BaseDirector() = default;

BaseDirector::BaseDirector(std::shared_ptr<BaseBuilder> builder) : builder(builder)
{
}
