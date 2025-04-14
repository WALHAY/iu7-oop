#include <hashmap/HashMapExceptions.hpp>

OutOfRangeException::OutOfRangeException(std::string filename, std::string classname, std::string method, int line) : BaseException(filename, classname, method, line, "Key not found!")
{
}

InvalidIterator::InvalidIterator(std::string filename, std::string classname, std::string method, int line) :
	BaseException(filename, classname, method, line, "Invalid Iterator") {}
