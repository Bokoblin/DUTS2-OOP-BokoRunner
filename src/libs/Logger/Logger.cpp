#include "Logger.h"

namespace Bokoblin
{
namespace SimpleLogger
{

std::string Logger::loggerFilename;

//------------------------------------------------
//          PUBLIC METHODS
//------------------------------------------------

/**
 * @brief Prints an info log line
 *
 * @param message the message to print along info tag
 *
 * @author Arthur
 * @date 12/10/2018
 */
void Logger::printInfo(const std::string& message)
{
#ifdef ENABLE_FILE_LOGGING
    printToFile(loggerFilename.empty() ? DEFAULT_LOGGER_FILE : loggerFilename, INFO_PREFIX, message);
#else
    printToConsole(INFO_PREFIX, message);
#endif
}

/**
 * @brief Prints a warning log line
 *
 * @param message the message to print along info tag
 *
 * @author Arthur
 * @date 12/10/2018
 */
void Logger::printWarning(const std::string& message)
{
#ifdef ENABLE_FILE_LOGGING
    printToFile(loggerFilename.empty() ? DEFAULT_LOGGER_FILE : loggerFilename, WARN_PREFIX, message);
#else
    printToConsole(WARN_PREFIX, message);
#endif
}

/**
 * @brief Prints an error log line
 *
 * @param message the message to print along info tag
 *
 * @author Arthur
 * @date 12/10/2018
 */
void Logger::printError(const std::string& message)
{
#ifdef ENABLE_FILE_LOGGING
    printToFile(loggerFilename.empty() ? DEFAULT_LOGGER_FILE : loggerFilename, ERROR_PREFIX, message);
#else
    printToConsole(ERROR_PREFIX, message);
#endif
}

/**
 * @brief Set the log file name and path
 *
 * @param filename the log file name
 *
 * @author Arthur
 * @date 12/10/2018
 */
void Logger::setLoggerFile(const std::string& filename)
{
    loggerFilename = filename;

    std::fstream f;
    f.open(filename.c_str(), std::ios::out);

    if (f.fail()) {
        printToConsole(ERROR_PREFIX, "Couldn't write to log file");
    } else {
        std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        f << std::ctime(&t) << std::endl;
    }
}


//------------------------------------------------
//          PRIVATE METHODS
//------------------------------------------------

/**
 * @brief Prints a log line to the console
 *
 * @param message the message to print along info tag
 * @param prefix the line prefix to indicate log category
 *
 * @author Arthur
 * @date 01/01/18 - 12/10/2018
 */
void Logger::printToConsole(const std::string& prefix, const std::string& message)
{
    if (prefix == ERROR_PREFIX) {
        std::cerr << prefix << message << std::endl;
    } else {
        std::cout << prefix << message << std::endl;
    }
}

/**
 * @brief Prints a log line to a file
 *
 * @param filename the file name
 * @param message the message to print
 * @param prefix the line prefix to indicate log category
 *
 * @author Arthur
 * @date 12/10/2018
 */
void Logger::printToFile(const std::string& filename, const std::string& prefix, const std::string& message)
{
    std::fstream f;
    f.open(filename.c_str(), std::ios::app);

    if (f.fail()) {
        printToConsole(ERROR_PREFIX, "Couldn't write to log file");
    } else {
        f << prefix << message << std::endl;
    }
}

} //namespace SimpleLogger
} //namespace Bokoblin
