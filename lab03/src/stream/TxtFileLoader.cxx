#include "stream/TxtFileLoader.hpp"

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
    // if (!exists(path))
    //     throw FileDoesNotExistException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));
    //
    // if (!is_regular_file(path))
    //     throw FileIsADirectoryException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));
    //
    auto newFile = std::make_shared<std::ifstream>(path);
    // if (!file_->is_open())
    //     throw FileIsNotOpeningException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));
    //
    file = newFile;
}

void TxtFileLoader::close()
{
    if (file->is_open())
        file->close();
}
