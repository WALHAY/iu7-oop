#include <objects/Model.hpp>
#include <visitors/ObjectVisitor.hpp>

Model::Model(std::shared_ptr<Wireframe> wireframeModel) : wireframeModel(wireframeModel)
{
}

void Model::accept(std::shared_ptr<ObjectVisitor> visitor)
{
    visitor->visit(*this);
}
