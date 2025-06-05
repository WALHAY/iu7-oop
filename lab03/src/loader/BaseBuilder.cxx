#include "objects/ObjectException.hpp"
#include <loader/BaseBuilder.hpp>

BaseBuilder::~BaseBuilder() = default;

void BaseBuilder::buildDirection(const Point &point)
{
	throw NotImplemented(__FILE_NAME__, __FUNCTION__, __LINE__);
}

void BaseBuilder::buildPoint(const Point &point)
{
	throw NotImplemented(__FILE_NAME__, __FUNCTION__, __LINE__);
}

void BaseBuilder::buildEdge(const Edge &edge)
{
	throw NotImplemented(__FILE_NAME__, __FUNCTION__, __LINE__);
}
