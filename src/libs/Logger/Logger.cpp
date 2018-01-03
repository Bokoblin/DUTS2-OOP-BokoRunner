#include "Logger.h"

namespace Bokoblin
{
namespace SimpleLogger
{

/**
 * Prints an info message on the console
 *
 * @param message the message to print along info tag
 *
 * @author Arthur
 * @date 01/01/18
 */
void Logger::printInfoOnConsole(const std::string &message)
{
    std::cout << "[INFO] " << message << std::endl;
}

/**
 * Prints a warning message on the console
 *
 * @param message the message to print along warning tag
 *
 * @author Arthur
 * @date 28/12/17
 */
void Logger::printWarningOnConsole(const std::string &message)
{
    std::cout << "[WARNING] " << message << std::endl;
}

/**
 * Prints an error message on the console
 *
 * @param message the message to print along error tag
 *
 * @author Arthur
 * @date 28/12/17
 */
void Logger::printErrorOnConsole(const std::string &message)
{
    std::cerr << "[ERROR] " << message << std::endl;
}

} //namespace SimpleLogger
} //namespace Bokoblin
