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

//=== Config
//FIXME: ALL THOSE CONFIGS ARE LINKED TO FILE BASED, WE SHALL ABSTRACT THAT ALSO
//TODO: Generate generate xml_document programmatically instead of having a giant string
//  That would allow a minimum file, especially for scores
extern const std::string CONFIG_FILE = Folder::RES + "config.xml";
extern const std::string TEST_CONFIG_FILE = "test_config.xml";
extern const std::string DEFAULT_CONFIG_CONTENT =
        "<?xml version=\"1.0\"?>\n"
        "<runner>\n"
        "\t<config>\n"
        "\t\t<configItem type=\"string\" name=\"language\" value=\"en\"/>\n"
        "\t\t<configItem type=\"int\" name=\"difficulty\" value=\"2\"/>\n"
        "\t\t<configItem type=\"string\" name=\"ball_skin\" value=\"default\"/>\n"
        "\t\t<configItem type=\"unsigned int\" name=\"wallet\" value=\"0\"/>\n"
        "\t\t<configItem type=\"boolean\" name=\"menu_music\" value=\"false\"/>\n"
        "\t\t<configItem type=\"boolean\" name=\"game_music\" value=\"true\"/>\n"
        "\t</config>\n"
        "\t<stats>\n"
        "\t\t<statItem type=\"unsigned int\" name=\"total_distance_travelled\" value=\"0\"/>\n"
        "\t\t<statItem type=\"unsigned int\" name=\"total_enemies_destroyed\" value=\"0\"/>\n"
        "\t\t<statItem type=\"unsigned int\" name=\"total_coins_collected\" value=\"0\"/>\n"
        "\t\t<statItem type=\"unsigned int\" name=\"total_games_played\" value=\"0\"/>\n"
        "\t\t<statItem type=\"unsigned int\" name=\"per_game_distance_travelled\" value=\"0\"/>\n"
        "\t\t<statItem type=\"unsigned int\" name=\"per_game_enemies_destroyed\" value=\"0\"/>\n"
        "\t\t<statItem type=\"unsigned int\" name=\"per_game_coins_collected\" value=\"0\"/>\n"
        "\t</stats>\n"
        "\t<shop>\n"
        "\t\t<shopItem type=\"boolean\" id=\"shop_doubler\" price=\"1000\" bought=\"false\"/>\n"
        "\t\t<shopItem type=\"boolean\" id=\"shop_shield_plus\" price=\"100\" bought=\"false\"/>\n"
        "\t\t<shopItem type=\"boolean\" id=\"shop_mega_plus\" price=\"200\" bought=\"false\"/>\n"
        "\t\t<shopItem type=\"boolean\" id=\"shop_fly_plus\" price=\"180\" bought=\"false\"/>\n"
        "\t\t<shopItem type=\"boolean\" id=\"shop_morphing\" price=\"500\" bought=\"false\"/>\n"
        "\t\t<shopItem type=\"boolean\" id=\"shop_capsule\" price=\"60\" bought=\"false\"/>\n"
        "\t</shop>\n"
        "\t<scoresEasy>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t</scoresEasy>\n"
        "\t<scoresHard>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
        "\t</scoresHard>\n"
        "</runner>";

} //namespace Resources
} //namespace View
} //namespace BokoRunner
} //namespace Bokoblin
