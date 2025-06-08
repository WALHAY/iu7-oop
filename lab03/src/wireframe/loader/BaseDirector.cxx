#include <wireframe/loader/BaseDirector.hpp>

BaseDirector::BaseDirector(std::shared_ptr<BaseBuilder> builder) : builder(builder){

}

BaseDirector::~BaseDirector() = default;
