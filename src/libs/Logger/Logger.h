/* Copyright 2017-2019 Jolivet Arthur

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <fstream>
#include <iostream>

namespace Bokoblin
{
namespace SimpleLogger
{

/**
 * The Logger class provides a trivial static logging system
 * by allowing writing either to the console or a file.
 *
 * The selection of the writing method is handles by a compile flag: ENABLE_FILE_LOGGING.
 * When enabled, in a CmakeLists.txt file for example, all print functions writes to
 * a predefined file which name and path is defined by the constant: DEFAULT_LOGGER_FILE.
 * When disabled, all print functions defaults to stdout for info and warnings or stderr for errors.
 *
 * It is also possible to change the log file name and path by calling the following function:
 * Logger::setLoggerFile().
 *
 * @author Arthur
 * @date 28/12/17 - 12/10/18
 */
class Logger
{
public:
    static void printInfo(const std::string& message);
    static void printWarning(const std::string& message);
    static void printError(const std::string& message);
    static void setLoggerFile(const std::string& filename);

private:
    static void printToConsole(const std::string& prefix, const std::string& message);
    static void printToFile(const std::string& filename, const std::string& prefix, const std::string& message);

    static std::string loggerFilename;
    static constexpr const char* INFO_PREFIX = "[INFO] ";
    static constexpr const char* WARN_PREFIX = "[WARNING] ";
    static constexpr const char* ERROR_PREFIX = "[ERROR] ";
    static constexpr const char* DEFAULT_LOGGER_FILE = "./app.log";
};

} //namespace SimpleLogger
} //namespace Bokoblin


#endif
