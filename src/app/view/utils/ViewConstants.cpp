#include "ViewConstants.h"

namespace Bokoblin
{
namespace BokoRunner
{
namespace Resources
{
namespace View
{
//=== Ressources Folders
namespace Folder
{
//=== Second-level folders
extern const std::string RESOURCES = "../res/";
extern const std::string AUDIO = RESOURCES + "audio/";
extern const std::string IMAGES = RESOURCES + "images/";
extern const std::string FONTS = RESOURCES + "fonts/";

//=== Images Sub-folders
extern const std::string BACKGROUNDS = Folder::IMAGES + "backgrounds/";
extern const std::string UI_COMPONENTS = Folder::IMAGES + "ui/";
extern const std::string GAME_COMPONENTS = Folder::IMAGES + "game_elements/";
}

//=== App values
extern const std::string APP_TITLE = "Boko Runner";
extern const unsigned int SCREEN_WIDTH = 900;
extern const unsigned int SCREEN_HEIGHT = 600;
extern const unsigned int SCREEN_BPP = 32;
extern const unsigned int APP_FRAMERATE = 30;
extern const std::string REPOSITORY_URL = "https://github.com/Bokoblin/DUTS2-OOP-BokoRunner";
extern const std::string EMAIL_URL = "mailto:jolivetarthur@gmail.com";

//=== Fonts files
extern const std::string ROBOTO_REGULAR_FONT = Folder::FONTS + "Roboto_Regular.ttf";
extern const std::string ROBOTO_CONDENSED_FONT = Folder::FONTS + "Roboto_Condensed.ttf";
extern const std::string ROBOTO_BOLD_FONT = Folder::FONTS + "Roboto_Bold.ttf";

//=== Images files : Backgrounds
extern const std::string GAME_FAR_HILL_BACKGROUND = Folder::BACKGROUNDS + "/hill_far.png";
extern const std::string GAME_NEAR_HILL_BACKGROUND = Folder::BACKGROUNDS + "/hill_near.png";
extern const std::string GAME_FAR_PLAIN_BACKGROUND = Folder::BACKGROUNDS + "/plain_far.png";
extern const std::string GAME_NEAR_PLAIN_BACKGROUND = Folder::BACKGROUNDS + "/plain_near.png";
extern const std::string GAME_FAR_T1_BACKGROUND = Folder::BACKGROUNDS + "/t1_far.png";
extern const std::string GAME_NEAR_T1_BACKGROUND = Folder::BACKGROUNDS + "/t1_near.png";
extern const std::string GAME_FAR_T2_BACKGROUND = Folder::BACKGROUNDS + "/t2_far.png";
extern const std::string GAME_NEAR_T2_BACKGROUND = Folder::BACKGROUNDS + "/t2_near.png";
extern const std::string PAUSE_HILL_BACKGROUND = Folder::BACKGROUNDS + "/pause_hill.png";
extern const std::string PAUSE_PLAIN_BACKGROUND = Folder::BACKGROUNDS + "/pause_plain.png";
extern const std::string END_SCREEN_BACKGROUND = Folder::BACKGROUNDS + "/end_background.png";

//=== Images files : UI components
extern const std::string MENU_BUTTON_IMAGE = Folder::UI_COMPONENTS + "menu_buttons.png";
extern const std::string SHAPE_BUTTONS_IMAGE = Folder::UI_COMPONENTS + "shape_buttons.png";
extern const std::string GAME_BUTTONS_IMAGE = Folder::UI_COMPONENTS + "game_buttons.png";
extern const std::string CARD_IMAGE = Folder::UI_COMPONENTS + "card.png";
extern const std::string HOME_IMAGE = Folder::UI_COMPONENTS + "ic_home.png";
extern const std::string HYPERLINK_IMAGE = Folder::UI_COMPONENTS + "ic_link.png";
extern const std::string PAGE_INDICATOR_IMAGE = Folder::UI_COMPONENTS + "indicator_buttons.png";

//=== Images files : Game components
extern const std::string BALL_IMAGE = Folder::GAME_COMPONENTS + "ball.png";
extern const std::string BONUS_IMAGE = Folder::GAME_COMPONENTS + "bonus.png";
extern const std::string ENEMIES_IMAGE = Folder::GAME_COMPONENTS + "enemies.png";
extern const std::string SHIELD_IMAGE = Folder::GAME_COMPONENTS + "shield.png";
extern const std::string BOTTOM_BAR_IMAGE = Folder::GAME_COMPONENTS + "bottom_bar.png";
extern const std::string LIFE_BOX_IMAGE = Folder::GAME_COMPONENTS + "life_bar.png";

//=== Images files : Misc
extern const std::string ICON_IMAGE = Folder::IMAGES + "app_icon.png";
extern const std::string SPLASH_SCREEN_IMAGE = Folder::IMAGES + "splash_screen.png";
extern const std::string TITLE_IMAGE = Folder::IMAGES + "title.png";
extern const std::string IUT_LOGO_IMAGE = Folder::IMAGES + "logo_iut.png";
extern const std::string SFML_LOGO_IMAGE = Folder::IMAGES + "logo_sfml.png";

//=== Musics files
extern const std::string MENU_MUSIC_THEME = Folder::AUDIO + "menu_sound.ogg";
extern const std::string GAME_MUSIC_THEME_EASY_MODE = Folder::AUDIO + "game_normal_sound.ogg";
extern const std::string GAME_MUSIC_THEME_HARD_MODE = Folder::AUDIO + "game_master_sound.ogg";
extern const std::string COINS_COLLECTED_MUSIC = Folder::AUDIO + "coin_collected_sound.ogg";
extern const std::string ENEMIES_DESTRUCTED_MUSIC = Folder::AUDIO + "destroyed_enemies_sound.ogg";

} //namespace Resources
} //namespace View
} //namespace BokoRunner
} //namespace Bokoblin
