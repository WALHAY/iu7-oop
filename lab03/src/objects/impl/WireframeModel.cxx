#include <objects/impl/WireframeModel.hpp>
#include <visitors/ObjectVisitor.hpp>

WireframeModel::WireframeModel(std::shared_ptr<Wireframe> wireframe) : wireframe(wireframe)
{
}

void WireframeModel::accept(std::shared_ptr<ObjectVisitor> visitor)
{
    visitor->visit(*this);
}
