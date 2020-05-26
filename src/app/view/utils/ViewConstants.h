/* Copyright 2018-2020 Jolivet Arthur

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

#ifndef VIEW_CONSTANTS_H
#define VIEW_CONSTANTS_H

#include <string>

namespace Bokoblin
{
namespace BokoRunner
{
namespace Resources
{

/**
 * @brief Provide constants to view classes
 *
 * @author Arthur
 * @date 11/02/18 - 02/05/2020
 */
namespace View
{

/**
 * @brief Folder constants
 */
namespace Folder
{
//=== Second level folders
extern const std::string RESOURCES;
extern const std::string AUDIO;
extern const std::string IMAGES;

//=== Images Sub-folders
extern const std::string BACKGROUNDS;
extern const std::string UI_COMPONENTS;
extern const std::string GAME_COMPONENTS;
}

//=== App values
extern const std::string APP_TITLE;
extern const unsigned int SCREEN_WIDTH;
extern const unsigned int SCREEN_HEIGHT;
extern const unsigned int SCREEN_BPP;
extern const unsigned int APP_FRAMERATE;
extern const std::string REPOSITORY_URL;
extern const std::string EMAIL_URL;

//=== Fonts files
extern const std::string ROBOTO_REGULAR_FONT;
extern const std::string ROBOTO_CONDENSED_FONT;
extern const std::string ROBOTO_BOLD_FONT;

//=== Images files : Backgrounds
extern const std::string GAME_FAR_HILL_BACKGROUND;
extern const std::string GAME_NEAR_HILL_BACKGROUND;
extern const std::string GAME_FAR_PLAIN_BACKGROUND;
extern const std::string GAME_NEAR_PLAIN_BACKGROUND;
extern const std::string GAME_FAR_T1_BACKGROUND;
extern const std::string GAME_NEAR_T1_BACKGROUND;
extern const std::string GAME_FAR_T2_BACKGROUND;
extern const std::string GAME_NEAR_T2_BACKGROUND;
extern const std::string PAUSE_HILL_BACKGROUND;
extern const std::string PAUSE_PLAIN_BACKGROUND;
extern const std::string END_SCREEN_BACKGROUND;

//=== Images files : UI components
extern const std::string MENU_BUTTON_IMAGE;
extern const std::string SHAPE_BUTTONS_IMAGE;
extern const std::string RESUME_BUTTON_IMAGE;
extern const std::string RESTART_BUTTON_IMAGE;
extern const std::string HOME_BUTTON_IMAGE;
extern const std::string MUSIC_BUTTON_IMAGE;
extern const std::string CARD_IMAGE;
extern const std::string HOME_IMAGE;
extern const std::string FLAG_IMAGE;
extern const std::string HYPERLINK_IMAGE;
extern const std::string PAGE_INDICATOR_IMAGE;

//=== Images files : Game components
extern const std::string PLAYER_IMAGE;
extern const std::string BONUS_IMAGE;
extern const std::string ENEMIES_IMAGE;
extern const std::string SHIELD_IMAGE;
extern const std::string BOTTOM_BAR_IMAGE;
extern const std::string LIFE_BOX_IMAGE;

//=== Images files : Misc
extern const std::string ICON_IMAGE;
extern const std::string SPLASH_SCREEN_IMAGE;
extern const std::string TITLE_IMAGE;
extern const std::string IUT_LOGO_IMAGE;
extern const std::string SFML_LOGO_IMAGE;

//=== Musics files
extern const std::string MENU_MUSIC_THEME;
extern const std::string GAME_MUSIC_THEME_EASY_MODE;
extern const std::string GAME_MUSIC_THEME_HARD_MODE;
extern const std::string COINS_COLLECTED_MUSIC;
extern const std::string ENEMIES_DESTRUCTED_MUSIC;

} //namespace Resources
} //namespace View
} //namespace BokoRunner
} //namespace Bokoblin

#endif
