#ifndef SHDOCUMENT_HANDLER_HPP
#define SHDOCUMENT_HANDLER_HPP

#include <experimental/filesystem>
#include <string>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include "../exception/Exception.hpp"

namespace nakhoadl {
    namespace Socket {
        class Handler {
            enum checker {
                Success,
                UnSuccess,
                FogotPass
            };

        public:
            /**
             * Create new directory
             *
             * @param path
             * @return `bool'
             */
            bool createDir(const std::string &path);

            /**
             * Create recursive directory
             *
             * @param path
             * @return `bool'
             */
            bool recursivelyCreateDir(const std::string &path);

            /**
             * Get all filename in target directory
             *
             * @param path
             * @return `std::vector<std::string>'
             */
            static std::vector<std::string> getAllFileName(const std::string pathToTargetDirectory);

            /**
             * Check whether user exist or not
             *
             * @param username
             * @param password
             * @return `checker'
             */
            static checker checkUser(const std::string username, const std::string password);

            static std::string *getContentFile(const std::string &filename);

            static std::vector<std::string*> *splitStringToVector(const std::string &target);

            static size_t getSizeOfFile(const std::string &filename);
         };
    } // End of namespace Socket
} // End of namespace nakhoadl

#endif //SHDOCUMENT_HANDLER_HPP
