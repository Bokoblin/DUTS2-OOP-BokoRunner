#include "AppTextManager.h"

using std::string;
using std::to_string;

//------------------------------------------------
//          CONSTRUCTOR / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs a text manager with
 * app core and window size
 *
 * @param appCore the app's core singleton
 * @param width the window width
 * @param height the window height
 *
 * @author Arthur
 * @date 02/04/16 - 06/01/18
 */
AppTextManager::AppTextManager(AppCore *appCore, unsigned int width, unsigned int height) :
        m_appCore{appCore}, m_width{width}, m_height{height}
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
AppTextManager::~AppTextManager()
{
    for (mdsf::Text *text : m_textList)
        delete text;
}


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Loads all managed standalone text
 * @author Arthur
 * @date 02/04/16 - 05/02/18
 * */
void AppTextManager::loadText()
{
    //=== Splash screen

    m_textList.push_back(m_splashScreenContinueLabel = new mdsf::Text("splash_screen_continue"));

    //=== Leaderboard

    m_textList.push_back(m_leaderboardTitleLabel = new mdsf::Text("leaderboard_title"));
    m_textList.push_back(m_leaderboardContentEasyText = new mdsf::Text("leaderboard_content"));
    m_textList.push_back(m_leaderboardContentHardText = new mdsf::Text("leaderboard_content"));

    //=== Commands

    m_textList.push_back(m_commandsTitleLabel = new mdsf::Text("commands_title"));
    m_textList.push_back(m_commandsPauseLabel = new mdsf::Text("commands_pause"));
    m_textList.push_back(m_commandsJumpLabel = new mdsf::Text("commands_jump"));
    m_textList.push_back(m_commandsLeftLabel = new mdsf::Text("commands_left"));
    m_textList.push_back(m_commandsRightLabel = new mdsf::Text("commands_right"));

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

    updateWholeStandaloneTextContent();
}


/**
 * Handle events related to link texts
 *
 * @param event sfml event object
 * @param settings the settings model
 *
 * @author Arthur
 * @date 02/11/17
 */
void AppTextManager::handleAboutLinks(sf::Event event, const SettingsModel &settings) const
{
    if (MOUSE_LEFT_PRESSED_EVENT)
    {
        if (m_aboutRepositoryLink->contains(MOUSE_POSITION))
            m_aboutRepositoryLink->setFillColor(AppColor::URLRed);
        if (m_aboutEmailLink->contains(MOUSE_POSITION))
            m_aboutEmailLink->setFillColor(AppColor::URLRed);
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        m_aboutRepositoryLink->setFillColor(sf::Color::White);
        m_aboutEmailLink->setFillColor(sf::Color::White);

        if (m_aboutRepositoryLink->contains(MOUSE_POSITION))
            settings.openURLinBrowser(REPOSITORY_URL);
        if (m_aboutEmailLink->contains(MOUSE_POSITION))
            settings.openURLinBrowser(EMAIL_URL);
    }
}


/**
 * Changes the content of all standalone texts
 * following current language
 *
 * @author Arthur
 * @date 13/04/16 - 04/02/17
 */
void AppTextManager::updateWholeStandaloneTextContent()
{
    for (mdsf::Text* t : m_textList)
    {
        t->setCharacterSize(DEFAULT_CHAR_SIZE);
        t->setFont(m_condensedFont);
        t->setFillColor(sf::Color::White);
        std::string utf8_string = PersistenceManager::fetchLocalizedString(t->getDescription());
        t->setString(sf::String::fromUtf8(utf8_string.begin(), utf8_string.end()));
    }
}


/**
 * Syncs splash screen standalone text
 *
 * @param continueVisibility the splash screen continue text visibility state
 *
 * @author Arthur
 * @date 31/10/17
 */
void AppTextManager::syncSplashScreenText(bool continueVisibility)
{
    m_splashScreenContinueLabel->setVisible(continueVisibility);
    m_splashScreenContinueLabel->setCharacterSize(DEFAULT_CHAR_SIZE);
    m_splashScreenContinueLabel->setPositionSelfCentered(m_width/2, 450);
}


/**
 * Syncs settings standalone text
 *
 * @param currentPage the current settings page opened
 *
 * @author Arthur
 * @date 14/04/16 - 03/11/17
 */
void AppTextManager::syncMenuSettingsText(int currentPage)
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
        m_statsTotalDistanceText->setString(to_string(m_appCore->getTotalDistance()) + " m");

        m_statsTotalEnemiesLabel->setPosition(STAT_LABEL_X, 230);
        m_statsTotalEnemiesLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalEnemiesText->setPosition(STAT_LABEL_X+250, 230);
        m_statsTotalEnemiesText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalEnemiesText->setStringFromInt(m_appCore->getTotalFlattenedEnemies());

        m_statsTotalCoinsLabel->setPosition(STAT_LABEL_X, 270);
        m_statsTotalCoinsLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalCoinsNbText->setPosition(STAT_LABEL_X+250, 270);
        m_statsTotalCoinsNbText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalCoinsNbText->setFillColor(sf::Color::White);
        m_statsTotalCoinsNbText->setStringFromInt(m_appCore->getTotalCoinsNumber());

        m_statsTotalGamesLabel->setPosition(STAT_LABEL_X, 310);
        m_statsTotalGamesLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalGamesText->setPosition(STAT_LABEL_X+250, 310);
        m_statsTotalGamesText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalGamesText->setStringFromInt(m_appCore->getTotalGamesPlayed());

        m_statsPerGameDistanceLabel->setPosition(m_width/2+STAT_LABEL_X, 190);
        m_statsPerGameDistanceLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameDistanceText->setPosition(m_width-2*STAT_LABEL_X, 190);
        m_statsPerGameDistanceText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameDistanceText->setString(to_string(m_appCore->getPerGameDistance()) + " m");

        m_statsPerGameEnemiesLabel->setPosition(m_width/2+STAT_LABEL_X, 230);
        m_statsPerGameEnemiesLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameEnemiesText->setPosition(m_width-2*STAT_LABEL_X, 230);
        m_statsPerGameEnemiesText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameEnemiesText->setStringFromInt(m_appCore->getPerGameFlattenedEnemies());

        m_statsPerGameCoinsLabel->setPosition(m_width/2+STAT_LABEL_X, 270);
        m_statsPerGameCoinsLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameCoinsText->setPosition(m_width-2*STAT_LABEL_X, 270);
        m_statsPerGameCoinsText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameCoinsText->setStringFromInt(m_appCore->getPerGameCoinsNumber());
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
 * Inits leaderboard standalone text
 *
 * @author Arthur
 * @date 27/12/17
 */
void AppTextManager::initMenuLeaderboardText()
{
    string scoresEasy = m_appCore->stringifyLeaderboard(EASY);
    string scoresHard = m_appCore->stringifyLeaderboard(HARD);

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
 * Syncs leaderboard standalone text
 *
 * @author Arthur
 * @date 19/04/16 - 30/01/17
 */
void AppTextManager::syncMenuLeaderboardText()
{
    if (m_appCore->isScoreEasyArrayEmpty())
    {
        m_leaderboardContentEasyText->setPositionSelfCentered(m_width/4, m_height/2);
    }
    else
    {
        m_leaderboardContentEasyText->setCharacterSize(26);
        m_leaderboardContentEasyText->setPositionSelfCentered(m_width/4, 300);
    }

    if (m_appCore->isScoreHardArrayEmpty())
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
 * Syncs commands standalone text
 *
 * @author Arthur
 * @date 05/02/18
 */
void AppTextManager::syncMenuCommandsText()
{
    m_commandsTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);

    m_commandsPauseLabel->setPosition(STAT_LABEL_X, 190);
    m_commandsPauseLabel->setCharacterSize(CONTENT_CHAR_SIZE);

    m_commandsJumpLabel->setPosition(STAT_LABEL_X, 230);
    m_commandsJumpLabel->setCharacterSize(CONTENT_CHAR_SIZE);

    m_commandsLeftLabel->setPosition(STAT_LABEL_X, 270);
    m_commandsLeftLabel->setCharacterSize(CONTENT_CHAR_SIZE);

    m_commandsRightLabel->setPosition(STAT_LABEL_X, 310);
    m_commandsRightLabel->setCharacterSize(CONTENT_CHAR_SIZE);
}


/**
 * Syncs shop standalone text
 * @author Arthur
 * @date 16/05/16 - 07/01/17
 */
void AppTextManager::syncMenuShopText()
{
    m_walletText->setPosition(m_width/2, TITLE_TEXT_X);
    m_walletText->applyTextFont(ROBOTO_CONDENSED_FONT, DEFAULT_CHAR_SIZE, AppColor::CoinGold);
    m_walletText->setStringFromInt(m_appCore->getWallet());
}


/**
 * Syncs running game standalone text
 *
 * @param bonusTimeout the current bonus timeout
 *
 * @author Arthur
 * @date 02/04/16 - 02/01/18
 */
void AppTextManager::syncGameRunningText(int bonusTimeout)
{
    m_playerLifeLabel->setPosition(40, 545);

    m_currentDistanceLabel->setPosition(440, 545);
    m_currentDistanceText->setPosition(640, 545);
    m_currentDistanceText->setFillColor(sf::Color::White);
    m_currentDistanceText->setString(to_string(m_appCore->getCurrentDistance()) + " m");

    m_bonusTimeoutText->setPosition(840, 545);
    m_bonusTimeoutText->setVisible(bonusTimeout > 0);
    m_bonusTimeoutText->setStringFromInt(bonusTimeout);
}


/**
 * Syncs paused game standalone text
 *
 * @author Arthur
 * @date 02/04/16 - 27/10/17
 */
void AppTextManager::syncGamePausedText()
{
    m_currentDistanceText->setPosition(PAUSE_TEXT_X, 30);

    m_currentCoinsNbText->setPosition(PAUSE_TEXT_X, 70);
    m_currentCoinsNbText->setFillColor(AppColor::CoinGold);
    m_currentCoinsNbText->setStringFromInt(m_appCore->getCurrentCoinsNumber());

    m_flattenedEnemiesText->setPosition(PAUSE_TEXT_X, 110);
    m_flattenedEnemiesText->setFillColor(AppColor::EnemyBlue);
    m_flattenedEnemiesText->setStringFromInt(m_appCore->getCurrentFlattenedEnemies());
}


/**
 * Syncs game over standalone text
 *
 * @param gameSpeed the last game speed before game over
 *
 * @author Arthur
 * @date 02/04/16 - 27/10/17
 */
void AppTextManager::syncGameOverText(int gameSpeed)
{
    m_endTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
    m_endTitleLabel->setFont(m_BoldFont);

    m_speedMultiplierLabel->setPosition(SUBTOTAL_LABEL_X, 170);
    m_speedMultiplierText->setPosition(SUBTOTAL_VALUE_X, 170);
    m_speedMultiplierText->setFillColor(AppColor::ScoreGrey);
    m_speedMultiplierText->setStringFromInt(gameSpeed);

    m_currentDistanceLabel->setPosition(SUBTOTAL_LABEL_X, 207);
    m_currentDistanceLabel->setFillColor(sf::Color::White);
    m_currentDistanceText->setPosition(SUBTOTAL_VALUE_X, 207);
    m_currentDistanceText->setFillColor(AppColor::ScoreGrey);
    m_currentDistanceText->setString(to_string(m_appCore->getCurrentDistance()) + " m");

    m_coinsCollectedLabel->setPosition(SUBTOTAL_LABEL_X, 245);
    m_currentCoinsNbText->setPosition(SUBTOTAL_VALUE_X, 245);
    m_currentCoinsNbText->setFillColor(AppColor::ScoreGrey);
    m_currentCoinsNbText->setString(to_string(m_appCore->getCurrentCoinsNumber()) + "  X  20");
    m_statsTotalCoinsNbText->setStringFromInt(m_appCore->getTotalCoinsNumber());

    m_flattenedEnemiesLabel->setPosition(SUBTOTAL_LABEL_X, 290);
    m_flattenedEnemiesLabel->setFillColor(sf::Color::White);
    m_flattenedEnemiesText->setPosition(SUBTOTAL_VALUE_X, 290);
    m_flattenedEnemiesText->setFillColor(AppColor::ScoreGrey);
    m_flattenedEnemiesText->setStringFromInt(m_appCore->getCurrentFlattenedEnemies());

    m_currentScoreLabel->setPosition(SUBTOTAL_LABEL_X, 350);
    m_currentScoreLabel->setFont(m_BoldFont);
    m_currentScoreText->setPosition(SUBTOTAL_VALUE_X, 350);
    m_currentScoreText->setFont(m_BoldFont);
    m_currentScoreText->setStringFromInt(m_appCore->getCurrentScore());

    m_walletText->applyTextFont(ROBOTO_CONDENSED_FONT, DEFAULT_CHAR_SIZE, AppColor::CoinGold);
    m_walletText->setPosition(m_width/2-15, 535);
    m_walletText->setStringFromInt(m_appCore->getWallet());
}



/**
 * Draws splash screen standalone text
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 31/10/17
 */
void AppTextManager::drawSplashScreenText(sf::RenderWindow *window) const
{
    m_splashScreenContinueLabel->draw(window);
}


/**
 * Draws settings standalone text
 *
 * @param window the app's window
 * @param currentPage the current settings page opened
 *
 * @author Arthur
 * @date 14/04/16 - 30/01/17
 */
void AppTextManager::drawMenuSettingsText(sf::RenderWindow *window, int currentPage) const
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
 * Draws leaderboard standalone text
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 19/04/16 - 05/02/18
 */
void AppTextManager::drawMenuLeaderboardText(sf::RenderWindow *window) const
{
    m_leaderboardTitleLabel->draw(window);
    m_leaderboardContentEasyText->draw(window);
    m_leaderboardContentHardText->draw(window);
}


/**
 * Draws commands standalone text
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 05/02/18
 */
void AppTextManager::drawMenuCommandsText(sf::RenderWindow *window) const
{
    m_commandsTitleLabel->draw(window);
    m_commandsPauseLabel->draw(window);
    m_commandsJumpLabel->draw(window);
    m_commandsLeftLabel->draw(window);
    m_commandsRightLabel->draw(window);
}


/**
 * Draws shop standalone text
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 16/05/16 - 04/01/17
 */
void AppTextManager::drawMenuShopText(sf::RenderWindow *window) const
{
    m_walletText->draw(window);
}


/**
 * Draws running game standalone text
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 02/04/16 - 02/01/17
 */
void AppTextManager::drawGameRunningText(sf::RenderWindow *window) const
{
    m_playerLifeLabel->draw(window);
    m_currentDistanceLabel->draw(window);
    m_currentDistanceText->draw(window);
    m_bonusTimeoutText->draw(window);
}


/**
 * Draws paused game standalone text
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 02/04/16 - 02/01/17
 */
void AppTextManager::drawGamePausedText(sf::RenderWindow *window) const
{
    m_currentDistanceText->draw(window);
    m_currentCoinsNbText->draw(window);
    m_flattenedEnemiesText->draw(window);
}


/**
 * Draws game over standalone text
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 02/04/16 - 06/01/18
 */
void AppTextManager::drawGameOverText(sf::RenderWindow *window) const
{
    //verbose but better than foreach loop in m_textList (O(n) -> O(1))
    m_endTitleLabel->draw(window);
    m_speedMultiplierLabel->draw(window);
    m_speedMultiplierText->draw(window);
    m_currentDistanceLabel->draw(window);
    m_coinsCollectedLabel->draw(window);
    m_flattenedEnemiesLabel->draw(window);
    m_flattenedEnemiesText->draw(window);
    m_currentScoreLabel->draw(window);
    m_currentScoreText->draw(window);
    m_currentDistanceText->draw(window);
    m_currentCoinsNbText->draw(window);
    m_walletText->draw(window);
}
