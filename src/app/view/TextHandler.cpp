#include "TextHandler.h"

using std::string;
using std::to_string;

/**
 * Constructs a text handler with
 * app's database and size
 * @author Arthur
 * @date 02/04/16 - 02/11/17
 *
 * @param dataBase the app database
 * @param width the app width
 * @param height the app height
 */
TextHandler::TextHandler(DataBase *dataBase, float width, float height) :
        m_dataBase{dataBase}, m_width{width}, m_height{height}
{
    m_regularFont.loadFromFile(ROBOTO_REGULAR_FONT);
    m_condensedFont.loadFromFile(ROBOTO_CONDENSED_FONT);
    m_BoldFont.loadFromFile(ROBOTO_BOLD_FONT);

    loadText();
}


/**
 * Destructor
 * @author Arthur
 * @date 02/04/16 - 07/01/17
 */
TextHandler::~TextHandler()
{
    for (mdsf::Text *t : m_textList)
        delete t;
}


/**
 * Text Loading
 * @author Arthur
 * @date 02/04/16 - 31/10/17
 * */
void TextHandler::loadText()
{
    //=== Splash screen

    m_textList.push_back(m_splashScreenContinueLabel = new mdsf::Text("splash_screen_continue"));

    //=== Leaderboard

    m_textList.push_back(m_leaderboardTitleLabel = new mdsf::Text("leaderboard_title"));
    m_textList.push_back(m_leaderboardContentEasyText = new mdsf::Text("leaderboard_content"));
    m_textList.push_back(m_leaderboardContentHardText = new mdsf::Text("leaderboard_content"));

    //=== Shop

    m_textList.push_back(m_walletText = new mdsf::Text("wallet"));

    //=== Settings - configuration

    m_textList.push_back(m_configTitleLabel = new mdsf::Text("config_title"));
    m_textList.push_back(m_configLangTitleLabel = new mdsf::Text("config_lang_title"));
    m_textList.push_back(m_configDifficultyTitleLabel = new mdsf::Text("config_difficulty_title"));
    m_textList.push_back(m_configCustomTitleLabel = new mdsf::Text("config_custom_title"));
    m_textList.push_back(m_configMusicTitleLabel = new mdsf::Text("config_music_title"));

    //=== Settings - stats

    m_textList.push_back(m_statsTitleLabel = new mdsf::Text("stats_title"));
    m_textList.push_back(m_statsOverallTitleLabel = new mdsf::Text("stats_overall_title"));
    m_textList.push_back(m_statsPerGameTitleLabel = new mdsf::Text("stats_per_game_title"));
    m_textList.push_back(m_statsTotalDistanceLabel = new mdsf::Text("stats_distance"));
    m_textList.push_back(m_statsTotalCoinsNbText = new mdsf::Text("stats_coins_value"));
    m_textList.push_back(m_statsTotalDistanceText = new mdsf::Text("stats_distance"));
    m_textList.push_back(m_statsTotalEnemiesLabel = new mdsf::Text("stats_enemies"));
    m_textList.push_back(m_statsTotalGamesLabel = new mdsf::Text("stats_games_number"));
    m_textList.push_back(m_statsTotalEnemiesText = new mdsf::Text("stats_enemies_value"));
    m_textList.push_back(m_statsTotalCoinsLabel = new mdsf::Text("stats_coins"));
    m_textList.push_back(m_statsTotalGamesText = new mdsf::Text("stats_games_number_value"));
    m_textList.push_back(m_statsPerGameCoinsLabel = new mdsf::Text("stats_per_game_coins"));
    m_textList.push_back(m_statsPerGameCoinsText = new mdsf::Text("stats_per_game_coins"));
    m_textList.push_back(m_statsPerGameDistanceLabel = new mdsf::Text("stats_per_game_distance"));
    m_textList.push_back(m_statsPerGameDistanceText = new mdsf::Text("stats_per_game_distance"));
    m_textList.push_back(m_statsPerGameEnemiesLabel = new mdsf::Text("stats_per_game_enemies"));
    m_textList.push_back(m_statsPerGameEnemiesText = new mdsf::Text("stats_per_game_enemies"));

    //=== Settings - about

    m_textList.push_back(m_aboutTitleLabel = new mdsf::Text("about_title"));
    m_textList.push_back(m_aboutDescriptionLabel = new mdsf::Text("about_description"));
    m_textList.push_back(m_aboutRepositoryLabel = new mdsf::Text("about_repository"));
    m_textList.push_back(m_aboutRepositoryLink = new mdsf::Text("about_repo_address"));
    m_textList.push_back(m_aboutEmailLink = new mdsf::Text("about_email"));
    m_textList.push_back(m_aboutCopyrightLabel = new mdsf::Text("about_copyright"));

    //=== Game

    m_textList.push_back(m_currentDistanceText = new mdsf::Text("game_current_distance"));
    m_textList.push_back(m_playerLifeLabel = new mdsf::Text("game_player_life"));
    m_textList.push_back(m_bonusTimeoutText = new mdsf::Text("game_bonus_timeout_value"));
    m_textList.push_back(m_currentCoinsNbText = new mdsf::Text("game_current_coins_value"));

    //=== Game End

    m_textList.push_back(m_endTitleLabel = new mdsf::Text("end_title"));
    m_textList.push_back(m_speedMultiplierLabel = new mdsf::Text("end_speed_multiplier"));
    m_textList.push_back(m_speedMultiplierText = new mdsf::Text("end_speed_multiplier_value"));
    m_textList.push_back(m_currentDistanceLabel = new mdsf::Text("end_current_distance"));
    m_textList.push_back(m_coinsCollectedLabel = new mdsf::Text("end_coins_collected"));
    m_textList.push_back(m_flattenedEnemiesLabel = new mdsf::Text("end_enemies"));
    m_textList.push_back(m_flattenedEnemiesText = new mdsf::Text("end_enemies_value"));
    m_textList.push_back(m_currentScoreLabel = new mdsf::Text("end_score"));
    m_textList.push_back(m_currentScoreText = new mdsf::Text("end_score_value"));

    updateWholeText();
}


/**
 * Changes Language
 * @author Arthur
 * @date 13/04/16 - 27/10/17
 */
void TextHandler::updateWholeText()
{
    for (mdsf::Text* t : m_textList)
    {
        t->setCharacterSize(DEFAULT_CHAR_SIZE);
        t->setFont(m_condensedFont);
        t->setFillColor(sf::Color::White);
        std::string utf8_string = m_dataBase->loadTextFromIdentifier(t->getDescription());
        t->setString(sf::String::fromUtf8(utf8_string.begin(), utf8_string.end()));
    }
}


/**
 * Splash screen Text Syncing
 * @author Arthur
 * @date 31/10/17
 *
 * @param continueVisibility the splash screen continue text visibility state
 */
void TextHandler::syncSplashScreenText(bool continueVisibility)
{
    m_splashScreenContinueLabel->setVisible(continueVisibility);
    m_splashScreenContinueLabel->setCharacterSize(DEFAULT_CHAR_SIZE);
    m_splashScreenContinueLabel->setPositionSelfCentered(m_width/2, 450);
}


/**
 * Menu Settings Text Syncing
 * @author Arthur
 * @date 14/04/16 - 03/11/17
 *
 * @param currentPage the current settings page opened
 */
void TextHandler::syncSettingsText(int currentPage)
{
    if (currentPage == CONFIG)
    {
        m_configTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
        m_configLangTitleLabel->setPosition(40, 150);
        m_configDifficultyTitleLabel->setPosition(40, 370);
        m_configCustomTitleLabel->setPosition(m_width/2+40, 150);
        m_configMusicTitleLabel->setPosition(m_width/2 +40, 370);
    }
    else if (currentPage == STATS)
    {
        m_statsTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
        m_statsOverallTitleLabel->setPosition(40, 130);
        m_statsPerGameTitleLabel->setPosition(m_width/2 + 40, 130);

        m_statsTotalDistanceLabel->setPosition(STAT_LABEL_X, 190);
        m_statsTotalDistanceLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalDistanceText->setPosition(STAT_LABEL_X+250, 190);
        m_statsTotalDistanceText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalDistanceText->setString(to_string(m_dataBase->getTotalDistance()) + " m");

        m_statsTotalEnemiesLabel->setPosition(STAT_LABEL_X, 230);
        m_statsTotalEnemiesLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalEnemiesText->setPosition(STAT_LABEL_X+250, 230);
        m_statsTotalEnemiesText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalEnemiesText->setStringFromInt(m_dataBase->getTotalFlattenedEnemies());

        m_statsTotalCoinsLabel->setPosition(STAT_LABEL_X, 270);
        m_statsTotalCoinsLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalCoinsNbText->setPosition(STAT_LABEL_X+250, 270);
        m_statsTotalCoinsNbText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalCoinsNbText->setFillColor(sf::Color::White);
        m_statsTotalCoinsNbText->setStringFromInt(m_dataBase->getTotalCoinsNumber());

        m_statsTotalGamesLabel->setPosition(STAT_LABEL_X, 310);
        m_statsTotalGamesLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalGamesText->setPosition(STAT_LABEL_X+250, 310);
        m_statsTotalGamesText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalGamesText->setStringFromInt(m_dataBase->getTotalGamesPlayed());

        m_statsPerGameDistanceLabel->setPosition(m_width/2+STAT_LABEL_X, 190);
        m_statsPerGameDistanceLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameDistanceText->setPosition(m_width-2*STAT_LABEL_X, 190);
        m_statsPerGameDistanceText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameDistanceText->setString(to_string(m_dataBase->getPerGameDistance()) + " m");

        m_statsPerGameEnemiesLabel->setPosition(m_width/2+STAT_LABEL_X, 230);
        m_statsPerGameEnemiesLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameEnemiesText->setPosition(m_width-2*STAT_LABEL_X, 230);
        m_statsPerGameEnemiesText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameEnemiesText->setStringFromInt(m_dataBase->getPerGameFlattenedEnemies());

        m_statsPerGameCoinsLabel->setPosition(m_width/2+STAT_LABEL_X, 270);
        m_statsPerGameCoinsLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameCoinsText->setPosition(m_width-2*STAT_LABEL_X, 270);
        m_statsPerGameCoinsText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameCoinsText->setStringFromInt(m_dataBase->getPerGameCoinsNumber());
    }
    else //ABOUT
    {
        m_aboutTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
        m_aboutDescriptionLabel->setPosition(70, 150);
        m_aboutDescriptionLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_aboutRepositoryLabel->setPosition(70, 250);
        m_aboutRepositoryLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_aboutCopyrightLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_aboutCopyrightLabel->setPositionSelfCentered((int)m_width/2, 490);

        //Hyperlinks
        m_aboutRepositoryLink->setPosition(110, 275);
        m_aboutRepositoryLink->setCharacterSize(CONTENT_CHAR_SIZE);
        m_aboutRepositoryLink->setStyle(sf::Text::Style::Underlined);
        m_aboutEmailLink->setPosition(110, 367);
        m_aboutEmailLink->setCharacterSize(CONTENT_CHAR_SIZE);
        m_aboutEmailLink->setStyle(sf::Text::Style::Underlined);
    }
}


/**
 * Menu Leaderboard Text Init
 * @author Arthur
 * @date 27/12/17
 */
void TextHandler::initMenuLeaderboardText()
{
    string scoresEasy = m_dataBase->loadLeaderboardScores(EASY);
    string scoresHard = m_dataBase->loadLeaderboardScores(HARD);

    if (scoresEasy.empty())
    {
        m_leaderboardContentEasyText->setPositionSelfCentered(m_width/4, m_height/2);
    }
    else
    {
        m_leaderboardContentEasyText->setString(sf::String::fromUtf8(scoresEasy.begin(), scoresEasy.end()));
        m_leaderboardContentEasyText->setCharacterSize(26);
        m_leaderboardContentEasyText->setPositionSelfCentered(m_width/4, 300);
    }

    if (scoresHard.empty())
    {
        m_leaderboardContentHardText->setPositionSelfCentered(m_width/2+m_width/4, m_height/2);
    }
    else
    {
        m_leaderboardContentHardText->setString(sf::String::fromUtf8(scoresHard.begin(), scoresHard.end()));
        m_leaderboardContentHardText->setCharacterSize(26);
        m_leaderboardContentHardText->setPositionSelfCentered(m_width/2+m_width/4, 300);
    }

    m_leaderboardTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
}


/**
 * Menu Leaderboard Text Syncing
 * @author Arthur
 * @date 19/04/16 - 30/01/17
 */
void TextHandler::syncMenuLeaderboardText()
{
    if (m_dataBase->isScoreEasyArrayEmpty())
    {
        m_leaderboardContentEasyText->setPositionSelfCentered(m_width/4, m_height/2);
    }
    else
    {
        m_leaderboardContentEasyText->setCharacterSize(26);
        m_leaderboardContentEasyText->setPositionSelfCentered(m_width/4, 300);
    }

    if (m_dataBase->isScoreHardArrayEmpty())
    {
        m_leaderboardContentHardText->setPositionSelfCentered(m_width/2+m_width/4, m_height/2);
    }
    else
    {
        m_leaderboardContentHardText->setCharacterSize(26);
        m_leaderboardContentHardText->setPositionSelfCentered(m_width/2+m_width/4, 300);
    }

    m_leaderboardTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
}


/**
 * Menu Shop Text Syncing
 * @author Arthur
 * @date 16/05/16 - 07/01/17
 */
void TextHandler::syncShopText()
{
    m_walletText->setPosition(m_width/2, TITLE_TEXT_X);
    m_walletText->applyTextFont(ROBOTO_CONDENSED_FONT, DEFAULT_CHAR_SIZE, GOLD_COLOR);
    m_walletText->setStringFromInt(m_dataBase->getWallet());
}


/**
 * Game Screen Syncing
 * @author Arthur
 * @date 02/04/16 - 27/10/17
 *
 * @param bonusTimeout the current bonus timeout
 */
void TextHandler::syncGameText(int bonusTimeout)
{
    m_playerLifeLabel->setPosition(40, 545);
    m_currentDistanceLabel->setPosition(440, 545);
    m_currentDistanceText->setPosition(640, 545);
    m_currentDistanceText->setFillColor(sf::Color::White);
    m_currentDistanceText->setString(to_string(
            m_dataBase->getCurrentDistance()) + " m");
    m_bonusTimeoutText->setPosition(840, 545);
    if (bonusTimeout > 0) {
        m_bonusTimeoutText->setStringFromInt(bonusTimeout);
        m_bonusTimeoutText->setVisible(true);
    }
    else
        m_bonusTimeoutText->setVisible(false);
}


/**
 * Game Pause Screen Syncing
 * @author Arthur
 * @date 02/04/16 - 27/10/17
 */
void TextHandler::syncPauseText()
{
    m_currentDistanceText->setPosition(PAUSE_TEXT_X, 30);
    m_currentCoinsNbText->setPosition(PAUSE_TEXT_X, 70);
    m_currentCoinsNbText->setFillColor(GOLD_COLOR);
    m_currentCoinsNbText->setStringFromInt(m_dataBase->getCurrentCoinsNumber());

    m_flattenedEnemiesText->setPosition(PAUSE_TEXT_X, 110);
    m_flattenedEnemiesText->setFillColor(ENEMY_BLUE_COLOR);
    m_flattenedEnemiesText->setStringFromInt(m_dataBase->getCurrentFlattenedEnemies());
}


/**
 * Game End Screen Syncing
 * @author Arthur
 * @date 02/04/16 - 27/10/17
 *
 * @param gameSpeed the last game speed before game over
 */
void TextHandler::syncGameOverText(int gameSpeed)
{
    m_endTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
    m_endTitleLabel->setFont(m_BoldFont);

    m_speedMultiplierLabel->setPosition(SUBTOTAL_LABEL_X, 170);
    m_speedMultiplierText->setPosition(SUBTOTAL_VALUE_X, 170);
    m_speedMultiplierText->setFillColor(END_GREY_COLOR);
    m_speedMultiplierText->setStringFromInt(gameSpeed);

    m_currentDistanceLabel->setPosition(SUBTOTAL_LABEL_X, 207);
    m_currentDistanceLabel->setFillColor(sf::Color::White);
    m_currentDistanceText->setPosition(SUBTOTAL_VALUE_X, 207);
    m_currentDistanceText->setFillColor(END_GREY_COLOR);
    m_currentDistanceText->setString(to_string(m_dataBase->getCurrentDistance()) + " m");
    m_currentCoinsNbText->setString(to_string(m_dataBase->getCurrentCoinsNumber()) + "  X  20");

    m_coinsCollectedLabel->setPosition(SUBTOTAL_LABEL_X, 245);
    m_currentCoinsNbText->setPosition(SUBTOTAL_VALUE_X, 245);
    m_currentCoinsNbText->setFillColor(END_GREY_COLOR);
    m_statsTotalCoinsNbText->setStringFromInt(m_dataBase->getTotalCoinsNumber());

    m_flattenedEnemiesLabel->setPosition(SUBTOTAL_LABEL_X, 290);
    m_flattenedEnemiesLabel->setFillColor(sf::Color::White);
    m_flattenedEnemiesText->setPosition(SUBTOTAL_VALUE_X, 290);
    m_flattenedEnemiesText->setFillColor(END_GREY_COLOR);
    m_flattenedEnemiesText->setStringFromInt(m_dataBase->getCurrentFlattenedEnemies());

    m_currentScoreLabel->setPosition(SUBTOTAL_LABEL_X, 350);
    m_currentScoreLabel->setFont(m_BoldFont);
    m_currentScoreText->setPosition(SUBTOTAL_VALUE_X, 350);
    m_currentScoreText->setFont(m_BoldFont);
    m_currentScoreText->setStringFromInt(m_dataBase->getCurrentScore());

    m_walletText->applyTextFont(ROBOTO_CONDENSED_FONT, DEFAULT_CHAR_SIZE, GOLD_COLOR);
    m_walletText->setPosition(m_width/2-15, 535);
    m_walletText->setStringFromInt(m_dataBase->getWallet());
}



/**
 * Splash Screen Drawing
 * @author Arthur
 * @date 31/10/17
 *
 * @param window the app's window
 */
void TextHandler::drawSplashScreenText(sf::RenderWindow *window) const
{
    m_splashScreenContinueLabel->draw(window);
}


/**
 * Settings Screen Drawing
 * @author Arthur
 * @date 14/04/16 - 30/01/17
 *
 * @param window the app's window
 * @param currentPage the current settings page opened
 */
void TextHandler::drawMenuSettingsText(sf::RenderWindow *window, int currentPage) const
{
    switch(currentPage)
    {
        case CONFIG:
            for (const auto &text : m_textList)
                if (text->getDescription().find("config") != string::npos)
                    text->draw(window);
            break;
        case STATS:
            for (const auto &text : m_textList)
                if (text->getDescription().find("stats") != string::npos)
                    text->draw(window);
            break;
        case ABOUT:
            for (const auto &text : m_textList)
                if (text->getDescription().find("about") != string::npos)
                    text->draw(window);
            break;
        default:
            break;
    }
}


/**
 * Leaderboard Screen Drawing
 * @author Arthur
 * @date 19/04/16 - 30/01/17
 *
 * @param window the app's window
 */
void TextHandler::drawLeaderboardText(sf::RenderWindow *window) const
{
    for (const auto &text : m_textList)
        if (text->getDescription().find("leaderboard") != string::npos)
            text->draw(window);
}


/**
 * Shop Screen Drawing
 * @author Arthur
 * @date 16/05/16 - 04/01/17
 *
 * @param window the app's window
 */
void TextHandler::drawMenuShopText(sf::RenderWindow *window) const
{
    m_walletText->draw(window);
}


/**
 * Game Screen Drawing
 * @author Arthur
 * @date 02/04/16 - 02/01/17
 *
 * @param window the app's window
 */
void TextHandler::drawGameText(sf::RenderWindow *window) const
{
    m_playerLifeLabel->draw(window);
    m_currentDistanceLabel->draw(window);
    m_currentDistanceText->draw(window);
    m_bonusTimeoutText->draw(window);
}


/**
 * Pause Screen Drawing
 * @author Arthur
 * @date 02/04/16 - 02/01/17
 *
 * @param window the app's window
 */
void TextHandler::drawPauseText(sf::RenderWindow *window) const
{
    m_currentDistanceText->draw(window);
    m_currentCoinsNbText->draw(window);
    m_flattenedEnemiesText->draw(window);
}


/**
 * End Screen Drawing
 * @author Arthur
 * @date 02/04/16 - 30/01/17
 *
 * @param window the app's window
 */
void TextHandler::drawGameOverText(sf::RenderWindow *window) const
{
    for (const auto &text : m_textList)
        if (text->getDescription().find("end") != string::npos)
            text->draw(window);

    m_currentDistanceText->draw(window);
    m_currentCoinsNbText->draw(window);
    m_walletText->draw(window);
}


/**
 * Treats events related to link texts
 * @author Arthur
 * @date 02/11/17
 *
 * @param event sfml event object
 * @param settings the settings model
 */
void TextHandler::handleAboutLinks(sf::Event event, const Settings &settings) const
{
    //TODO : Temporary until dedicated LinkButton class

    if (MOUSE_LEFT_PRESSED_EVENT)
    {
        if (m_aboutRepositoryLink->contains(MOUSE_POSITION))
            m_aboutRepositoryLink->setFillColor(URL_RED_COLOR);
        if (m_aboutEmailLink->contains(MOUSE_POSITION))
            m_aboutEmailLink->setFillColor(URL_RED_COLOR);
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        m_aboutRepositoryLink->setFillColor(sf::Color::White);
        m_aboutEmailLink->setFillColor(sf::Color::White);

        if (m_aboutRepositoryLink->contains(MOUSE_POSITION))
            settings.openURLinBrowser(REPOSITORY);
        if (m_aboutEmailLink->contains(MOUSE_POSITION))
            settings.openURLinBrowser(EMAIL);
    }
}
