#include "Config.h"

using std::string;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

Config::logger_function Config::printError = Config::defaultPrintErrorFunction;

/**
 * @brief Prints an error message to stderr
 * @details Default method in case the application developer doesn't set the function pointer
 * @param message the message to print
 */
void Config::defaultPrintErrorFunction(const std::string& message)
{
    std::cerr << message << std::endl;
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
