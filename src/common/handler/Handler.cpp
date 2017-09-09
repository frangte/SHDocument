#include <unistd.h>
#include "Handler.hpp"

using namespace nakhoadl::Socket;
namespace fs = std::experimental::filesystem;

std::vector<std::string> Handler::getAllFileName(const std::string pathToTargetDirectory) {
    std::vector<std::string> resultVector;
    try {
        for (auto &p : fs::directory_iterator(pathToTargetDirectory)) {
            resultVector.push_back(p.path().c_str());
        }
    } catch (std::exception &exception) {
        std::cout << exception.what() << std::endl;
    }

    return resultVector;
}

bool Handler::createDir(const std::string &path) {
    return mkdir(path.c_str(),  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

bool Handler::recursivelyCreateDir(const std::string &path) {
    if (createDir(path)) return true;

    if (access(path.c_str(), F_OK) == 0) return false; // Exists path in this directory

    size_t slashPos = path.find_last_of('/');
    if (slashPos == std::string::npos) return false;

    return recursivelyCreateDir(path.substr(0, slashPos));
}

std::string *Handler::getContentFile(const std::string &filename) {
    std::ifstream fileIn(filename.c_str(), std::ios::binary);

    if (!fileIn.is_open()) {
        return nullptr;
    }

    auto *contentsFile = new std::string();
    fileIn.seekg(0, std::ios::end);
    contentsFile->resize(fileIn.tellg());
    fileIn.seekg(0, std::ios::beg);

    fileIn.read(&(*contentsFile)[0], contentsFile->size());
    fileIn.close();
    return contentsFile;
}
