/* Copyright 2016-2018 Jolivet Arthur & Laronze Florian

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

#ifndef MODEL_CONSTANTS_H
#define MODEL_CONSTANTS_H

#include <string>

/**
 * This file provides constants to model classes
 *
 * @author Arthur
 * @date 23/10/16 - 11/02/18
 */

//=== Ressources Folders
static const std::string RESOURCES_FOLDER = "../res/";
static const std::string STRINGS_FOLDER = RESOURCES_FOLDER + "strings/";

//=== Languages
static const std::string ENGLISH = "en";
static const std::string FRENCH = "fr";
static const std::string SPANISH = "es";

//=== Regex
static const std::string INTEGER_REGEX = "^(0|[1-9][0-9]*)$";
static const std::string BOOLEAN_REGEX = "true|false";

//=== Game values
static const int MAX_LIFE = 100;
static const int GAME_FLOOR = 480;
static const int PLAYER_RATE = 30;

//=== Language strings files
static const std::string ENGLISH_STRINGS = STRINGS_FOLDER + "english.xml";
static const std::string FRENCH_STRINGS = STRINGS_FOLDER + "french.xml";
static const std::string SPANISH_STRINGS = STRINGS_FOLDER + "spanish.xml";

//=== Config
static const std::string CONFIG_FILE = RESOURCES_FOLDER + "config.xml";
static const std::string TEST_CONFIG_FILE = "test_config.xml";
static const std::string DEFAULT_CONFIG_CONTENT =
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

#endif
