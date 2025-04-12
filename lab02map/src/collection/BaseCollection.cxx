#include "collection/BaseCollection.hpp"

BaseCollection::BaseCollection() {

}

BaseCollection::~BaseCollection() = default;

size_t BaseCollection::getSize() const {
	return this->size;
}

bool BaseCollection::isEmpty() const {
	return this->size == 0;
}


