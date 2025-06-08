#include <wireframe/loader/BaseModelDirector.hpp>

BaseModelDirector::BaseModelDirector(std::shared_ptr<BaseModelBuilder> builder) : builder(builder)
{
}

BaseModelDirector::~BaseModelDirector() = default;
