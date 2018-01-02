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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

/**
 * Provides constants to model and view classes
 * @author Arthur
 * @date 23/10/16 - 01/01/18
 */

//=== Ressources Folders
static const std::string RESOURCES_FOLDER = "../res/";
static const std::string AUDIO_FOLDER = RESOURCES_FOLDER + "audio/";
static const std::string IMAGE_FOLDER = RESOURCES_FOLDER + "images/";
static const std::string FONTS_FOLDER = RESOURCES_FOLDER + "fonts/";
static const std::string STRINGS_FOLDER = RESOURCES_FOLDER + "strings/";

//=== Config
static const std::string CONFIG_FILE = RESOURCES_FOLDER + "config.xml";
static const std::string DEFAULT_CONFIG_CONTENT = "<?xml version=\"1.0\"?>\n"
        "<runner>\n"
        "\t<config>\n"
        "\t\t<configItem name=\"language\" value=\"en\"/>\n"
        "\t\t<configItem name=\"difficulty\" value=\"2\"/>\n"
        "\t\t<configItem name=\"ball_skin\" value=\"default\"/>\n"
        "\t\t<configItem name=\"wallet\" value=\"0\"/>\n"
        "\t\t<configItem name=\"menu_music\" value=\"false\"/>\n"
        "\t\t<configItem name=\"game_music\" value=\"false\"/>\n"
        "\t</config>\n"
        "\t<stats>\n"
        "\t\t<statItem name=\"total_distance_travelled\" value=\"0\"/>\n"
        "\t\t<statItem name=\"total_enemies_destroyed\" value=\"0\"/>\n"
        "\t\t<statItem name=\"total_coins_collected\" value=\"0\"/>\n"
        "\t\t<statItem name=\"total_games_played\" value=\"0\"/>\n"
        "\t\t<statItem name=\"per_game_distance_travelled\" value=\"0\"/>\n"
        "\t\t<statItem name=\"per_game_enemies_destroyed\" value=\"0\"/>\n"
        "\t\t<statItem name=\"per_game_coins_collected\" value=\"0\"/>\n"
        "\t</stats>\n"
        "\t<shop>\n"
        "\t\t<shopItem id=\"shop_doubler\" price=\"1000\" bought=\"false\"/>\n"
        "\t\t<shopItem id=\"shop_shieldPlus\" price=\"100\" bought=\"false\"/>\n"
        "\t\t<shopItem id=\"shop_megaPlus\" price=\"200\" bought=\"false\"/>\n"
        "\t\t<shopItem id=\"shop_flyPlus\" price=\"180\" bought=\"false\"/>\n"
        "\t\t<shopItem id=\"shop_morphing\" price=\"500\" bought=\"false\"/>\n"
        "\t\t<shopItem id=\"shop_capsule\" price=\"60\" bought=\"false\"/>\n"
        "\t</shop>\n"
        "\t<scoresEasy>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t</scoresEasy>\n"
        "\t<scoresHard>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t\t<scoreItem value=\"0\"/>\n"
        "\t</scoresHard>\n"
        "</runner>";

//=== App
static const std::string APP_TITLE = "Boko Runner";
static const int SCREEN_WIDTH = 900;
static const int SCREEN_HEIGHT = 600;
static const int SCREEN_BPP = 32;
static const int FRAMERATE = 30;

//=== Languages
static const std::string ENGLISH = "en";
static const std::string FRENCH = "fr";
static const std::string SPANISH = "es";

//=== Game
static const int MAX_LIFE = 100;
static const int GAME_FLOOR = 480;

//=== Fonts
static const std::string ROBOTO_REGULAR_FONT = FONTS_FOLDER + "Roboto_Regular.ttf";
static const std::string ROBOTO_CONDENSED_FONT = FONTS_FOLDER + "Roboto_Condensed.ttf";
static const std::string ROBOTO_BOLD_FONT = FONTS_FOLDER + "Roboto_Bold.ttf";

//=== Images : Backgrounds
static const std::string DEFAULT_FAR_HILL_BACKGROUND = IMAGE_FOLDER + "backgrounds/hill_far.png";
static const std::string DEFAULT_NEAR_HILL_BACKGROUND = IMAGE_FOLDER + "backgrounds/hill_near.png";
static const std::string DEFAULT_FAR_PLAIN_BACKGROUND = IMAGE_FOLDER + "backgrounds/plain_far.png";
static const std::string DEFAULT_NEAR_PLAIN_BACKGROUND = IMAGE_FOLDER + "backgrounds/plain_near.png";
static const std::string DEFAULT_FAR_T1_BACKGROUND = IMAGE_FOLDER + "backgrounds/t1_far.png";
static const std::string DEFAULT_NEAR_T1_BACKGROUND = IMAGE_FOLDER + "backgrounds/t1_near.png";
static const std::string DEFAULT_FAR_T2_BACKGROUND = IMAGE_FOLDER + "backgrounds/t2_far.png";
static const std::string DEFAULT_NEAR_T2_BACKGROUND = IMAGE_FOLDER + "backgrounds/t2_near.png";
static const std::string PAUSE_HILL_BACKGROUND = IMAGE_FOLDER + "backgrounds/pause_hill.png";
static const std::string PAUSE_PLAIN_BACKGROUND = IMAGE_FOLDER + "backgrounds/pause_plain.png";
static const std::string END_SCREEN_BACKGROUND = IMAGE_FOLDER + "backgrounds/end_background.png";

//=== Images : UI components
static const std::string RECT_BUTTONS_IMAGE = IMAGE_FOLDER + "ui/rect_buttons.png";
static const std::string SHAPE_BUTTONS_IMAGE = IMAGE_FOLDER + "ui/shape_buttons.png";
static const std::string GAME_BUTTONS_IMAGE = IMAGE_FOLDER + "ui/game_buttons.png";
static const std::string CARD_IMAGE = IMAGE_FOLDER + "ui/card.png";

//=== Images : Game components
static const std::string BALL_IMAGE = IMAGE_FOLDER + "game_elements/ball.png";
static const std::string BONUS_IMAGE = IMAGE_FOLDER + "game_elements/bonus.png";
static const std::string ENEMIES_IMAGE = IMAGE_FOLDER + "game_elements/enemies.png";
static const std::string SHIELD_IMAGE = IMAGE_FOLDER + "game_elements/shield.png";
static const std::string BOTTOM_BAR_IMAGE = IMAGE_FOLDER + "game_elements/bottom_bar.png";
static const std::string LIFE_BOX_IMAGE = IMAGE_FOLDER + "game_elements/life_bar.png";

//=== Images : Misc
static const std::string ICON_IMAGE = IMAGE_FOLDER + "app_icon.png";
static const std::string SPLASH_SCREEN_IMAGE = IMAGE_FOLDER + "splash_screen.png";
static const std::string TITLE_IMAGE = IMAGE_FOLDER + "title.png";
static const std::string IUT_LOGO_IMAGE = IMAGE_FOLDER + "logo_iut.png";
static const std::string SFML_LOGO_IMAGE = IMAGE_FOLDER + "logo_sfml.png";
static const std::string COMMAND_EN_IMAGE = IMAGE_FOLDER + "command_en.png"; //TODO-1 : only one image with translations
static const std::string COMMAND_FR_IMAGE = IMAGE_FOLDER + "command_fr.png"; //TODO-2 : or in list without keyboard image
static const std::string COMMAND_ES_IMAGE = IMAGE_FOLDER + "command_es.png"; //TODO-3 : in order to have configuration later

//=== Musics
static const std::string MENU_MUSIC_THEME = AUDIO_FOLDER + "menu_sound.ogg";
static const std::string GAME_MUSIC_THEME_EASY_MODE = AUDIO_FOLDER + "game_normal_sound.ogg";
static const std::string GAME_MUSIC_THEME_HARD_MODE = AUDIO_FOLDER + "game_master_sound.ogg";
static const std::string COINS_COLLECTED_MUSIC = AUDIO_FOLDER + "coin_collected_sound.ogg";
static const std::string ENEMIES_DESTRUCTED_MUSIC = AUDIO_FOLDER + "destroyed_enemies_sound.ogg";

//=== Strings
static const std::string ENGLISH_STRINGS = STRINGS_FOLDER + "english.xml";
static const std::string FRENCH_STRINGS = STRINGS_FOLDER + "french.xml";
static const std::string SPANISH_STRINGS = STRINGS_FOLDER + "spanish.xml";

#endif
