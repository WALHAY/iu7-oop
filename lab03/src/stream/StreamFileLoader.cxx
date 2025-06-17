#include "stream/StreamFileLoader.hpp"

StreamFileLoader::StreamFileLoader(std::shared_ptr<BaseFileLoader> fileLoader)
{
    this->fileLoader = fileLoader;
}

std::shared_ptr<std::istream> StreamFileLoader::getStream()
{
    return fileLoader->get();
}


void StreamFileLoader::closeStream()
{
    fileLoader->close();
}
