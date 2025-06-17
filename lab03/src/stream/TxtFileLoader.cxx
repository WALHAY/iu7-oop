#include "stream/TxtFileLoader.hpp"
#include "stream/StreamExceptions.hpp"

TxtFileLoader::TxtFileLoader(const std::filesystem::path &path)
{
    this->path = path;
}

std::shared_ptr<std::ifstream> TxtFileLoader::get()
{
    if (file == nullptr)
        open();

    return file;
}

void TxtFileLoader::open()
{
    if (!exists(path))
        throw FileNotExistException(__FILE__, __FUNCTION__, __LINE__);

    if (!is_regular_file(path))
        throw NotAFileException(__FILE__, __FUNCTION__, __LINE__);

    auto newFile = std::make_shared<std::ifstream>(path);
    if (!newFile->is_open())
        throw FileOpenException(__FILE__, __FUNCTION__, __LINE__);

    file = newFile;
}

void TxtFileLoader::close()
{
    if (file->is_open())
        file->close();
}
