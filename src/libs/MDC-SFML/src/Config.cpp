#include "Config.h"

using std::string;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

Config::logger_function Config::printError = [](const std::string& message) {
    std::cerr << message << std::endl;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
