#include "collection/BaseCollection.hpp"

BaseCollection::BaseCollection() {
}

BaseCollection::~BaseCollection() = default;

bool BaseCollection::isEmpty() const {
	return getSize() == 0;
}


