#include "ModelConstants.h"

namespace Bokoblin
{
namespace BokoRunner
{
namespace Resources
{
namespace Model
{
//=== Ressources Folders
namespace Folder
{
extern const std::string RES = "../res/";
extern const std::string SOURCES = "../src/";
extern const std::string TESTS = "../test/";
extern const std::string LOCALIZATION = RES + "strings/";
}

//=== Languages
extern const std::string ENGLISH = "en";
extern const std::string FRENCH = "fr";
extern const std::string SPANISH = "es";

//=== Regex
extern const std::string INTEGER_REGEX = "^(0|[1-9][0-9]*)$";
extern const std::string BOOLEAN_REGEX = "true|false";

//=== Language strings files
extern const std::string ENGLISH_STRINGS = Folder::LOCALIZATION + "english.xml";
extern const std::string FRENCH_STRINGS = Folder::LOCALIZATION + "french.xml";
extern const std::string SPANISH_STRINGS = Folder::LOCALIZATION + "spanish.xml";

} //namespace Resources
} //namespace View
} //namespace BokoRunner
} //namespace Bokoblin
