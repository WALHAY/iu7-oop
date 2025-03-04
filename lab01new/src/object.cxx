#include "object.hpp"

struct object {
	edges_t edges;
};

object_t init_object()
{
	static object_t obj;

	return obj;
}
