/* Copyright 2018 Jolivet Arthur

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
#include "app/model/core/ModelConstants.h"

/**
 * Provides constants to view classes
 *
 * @author Arthur
 * @date 11/02/18 - 11/09/18
 */

//=== Ressources Folders
static const std::string AUDIO_FOLDER = RESOURCES_FOLDER + "audio/";
static const std::string IMAGE_FOLDER = RESOURCES_FOLDER + "images/";
static const std::string FONTS_FOLDER = RESOURCES_FOLDER + "fonts/";

//=== Images Sub-folders
static const std::string BACKGROUND_FOLDER = IMAGE_FOLDER + "backgrounds/";
static const std::string UI_FOLDER = IMAGE_FOLDER + "ui/";
static const std::string GAME_COMPONENTS_FOLDER = IMAGE_FOLDER + "game_elements/";

//=== App values
static const std::string APP_TITLE = "Boko Runner";
static const int SCREEN_WIDTH = 900;
static const int SCREEN_HEIGHT = 600;
static const int SCREEN_BPP = 32;
static const int APP_FRAMERATE = 30;
static const std::string REPOSITORY_URL = "https://github.com/Bokoblin/DUTS2-POO-ProjetRunner";
static const std::string EMAIL_URL = "mailto:pro.jolivetarthur@gmail.com";

//=== Fonts files
static const std::string ROBOTO_REGULAR_FONT = FONTS_FOLDER + "Roboto_Regular.ttf";
static const std::string ROBOTO_CONDENSED_FONT = FONTS_FOLDER + "Roboto_Condensed.ttf";
static const std::string ROBOTO_BOLD_FONT = FONTS_FOLDER + "Roboto_Bold.ttf";

//=== Images files : Backgrounds
static const std::string GAME_FAR_HILL_BACKGROUND = BACKGROUND_FOLDER + "/hill_far.png";
static const std::string GAME_NEAR_HILL_BACKGROUND = BACKGROUND_FOLDER + "/hill_near.png";
static const std::string GAME_FAR_PLAIN_BACKGROUND = BACKGROUND_FOLDER + "/plain_far.png";
static const std::string GAME_NEAR_PLAIN_BACKGROUND = BACKGROUND_FOLDER + "/plain_near.png";
static const std::string GAME_FAR_T1_BACKGROUND = BACKGROUND_FOLDER + "/t1_far.png";
static const std::string GAME_NEAR_T1_BACKGROUND = BACKGROUND_FOLDER + "/t1_near.png";
static const std::string GAME_FAR_T2_BACKGROUND = BACKGROUND_FOLDER + "/t2_far.png";
static const std::string GAME_NEAR_T2_BACKGROUND = BACKGROUND_FOLDER + "/t2_near.png";
static const std::string PAUSE_HILL_BACKGROUND = BACKGROUND_FOLDER + "/pause_hill.png";
static const std::string PAUSE_PLAIN_BACKGROUND = BACKGROUND_FOLDER + "/pause_plain.png";
static const std::string END_SCREEN_BACKGROUND = BACKGROUND_FOLDER + "/end_background.png";

//=== Images files : UI components
static const std::string RAISED_BUTTON_IMAGE = UI_FOLDER + "raised_buttons.png";
static const std::string MENU_BUTTON_IMAGE = UI_FOLDER + "menu_buttons.png";
static const std::string SHAPE_BUTTONS_IMAGE = UI_FOLDER + "shape_buttons.png";
static const std::string GAME_BUTTONS_IMAGE = UI_FOLDER + "game_buttons.png";
static const std::string CARD_IMAGE = UI_FOLDER + "card.png";
static const std::string HOME_IMAGE = UI_FOLDER + "ic_home.png";
static const std::string HYPERLINK_IMAGE = UI_FOLDER + "ic_link.png";

//=== Images files : Game components
static const std::string BALL_IMAGE = GAME_COMPONENTS_FOLDER + "ball.png";
static const std::string BONUS_IMAGE = GAME_COMPONENTS_FOLDER + "bonus.png";
static const std::string ENEMIES_IMAGE = GAME_COMPONENTS_FOLDER + "enemies.png";
static const std::string SHIELD_IMAGE = GAME_COMPONENTS_FOLDER + "shield.png";
static const std::string BOTTOM_BAR_IMAGE = GAME_COMPONENTS_FOLDER + "bottom_bar.png";
static const std::string LIFE_BOX_IMAGE = GAME_COMPONENTS_FOLDER + "life_bar.png";

//=== Images files : Misc
static const std::string ICON_IMAGE = IMAGE_FOLDER + "app_icon.png";
static const std::string SPLASH_SCREEN_IMAGE = IMAGE_FOLDER + "splash_screen.png";
static const std::string TITLE_IMAGE = IMAGE_FOLDER + "title.png";
static const std::string IUT_LOGO_IMAGE = IMAGE_FOLDER + "logo_iut.png";
static const std::string SFML_LOGO_IMAGE = IMAGE_FOLDER + "logo_sfml.png";

//=== Musics files
static const std::string MENU_MUSIC_THEME = AUDIO_FOLDER + "menu_sound.ogg";
static const std::string GAME_MUSIC_THEME_EASY_MODE = AUDIO_FOLDER + "game_normal_sound.ogg";
static const std::string GAME_MUSIC_THEME_HARD_MODE = AUDIO_FOLDER + "game_master_sound.ogg";
static const std::string COINS_COLLECTED_MUSIC = AUDIO_FOLDER + "coin_collected_sound.ogg";
static const std::string ENEMIES_DESTRUCTED_MUSIC = AUDIO_FOLDER + "destroyed_enemies_sound.ogg";

#endif
