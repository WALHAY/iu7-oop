#include "interface/managers/ManagersExceptions.hpp"
#include "visitors/TransformVisitor.hpp"
#include <interface/managers/TransformManager.hpp>

void TransformManager::setSelectionManager(std::shared_ptr<SelectionManager> selectionManager)
{
    this->selectionManager = selectionManager;
}

void TransformManager::transform(const Matrix<double> &matrix)
{
	if(!selectionManager)
		throw SelectionManagerNotSetException(__FILE_NAME__, __FUNCTION__, __LINE__);

    std::shared_ptr<TransformVisitor> visitor = std::make_shared<TransformVisitor>(matrix);

    for (auto &obj : *(selectionManager->getSelection()))
        obj->accept(visitor);
}
