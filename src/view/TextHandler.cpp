#include "TextHandler.h"

using namespace std;

/**
 * Constructs a text handler with
 * app's database and size
 * @author Arthur
 * @date 02/04/16 - 07/01/17
 */
TextHandler::TextHandler(DataBase *dataBase, float width, float height)
        : m_dataBase{dataBase}, m_width{width}, m_height{height}
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
    for (Text *t : m_textList)
        delete t;
}


//=== Getters

const sf::Font& TextHandler::getRegularFont() const { return m_regularFont; }
const sf::Font& TextHandler::getCondensedFont() const { return m_condensedFont; }
const sf::Font& TextHandler::getBoldFont() const { return m_BoldFont; }


/**
 * Text Loading
 * @author Arthur
 * @date 02/04/16 - 30/01/17
 * */
void TextHandler::loadText()
{
    //=== Leaderboard

    m_textList.push_back(m_leaderboardTitleLabel = new Text("leaderboard_title"));
    m_textList.push_back(m_leaderboardContentEasyText = new Text("leaderboard_content"));
    m_textList.push_back(m_leaderboardContentHardText = new Text("leaderboard_content"));

    //=== Shop

    m_textList.push_back(m_walletText = new Text("wallet"));

    //=== Settings - configuration

    m_textList.push_back(m_configTitleLabel = new Text("config_title"));
    m_textList.push_back(m_configLangTitleLabel = new Text("config_lang_title"));
    m_textList.push_back(m_configDifficultyTitleLabel = new Text("config_difficulty_title"));
    m_textList.push_back(m_configCustomTitleLabel = new Text("config_custom_title"));
    m_textList.push_back(m_configMusicTitleLabel = new Text("config_music_title"));

    //=== Settings - stats

    m_textList.push_back(m_statsTitleLabel = new Text("stats_title"));
    m_textList.push_back(m_statsOverallTitleLabel = new Text("stats_overall_title"));
    m_textList.push_back(m_statsPerGameTitleLabel = new Text("stats_per_game_title"));
    m_textList.push_back(m_statsTotalDistanceLabel = new Text("stats_distance"));
    m_textList.push_back(m_statsTotalCoinsNbText = new Text("stats_coins_value"));
    m_textList.push_back(m_statsTotalDistanceText = new Text("stats_distance"));
    m_textList.push_back(m_statsTotalEnemiesLabel = new Text("stats_enemies"));
    m_textList.push_back(m_statsTotalGamesLabel = new Text("stats_games_number"));
    m_textList.push_back(m_statsTotalEnemiesText = new Text("stats_enemies_value"));
    m_textList.push_back(m_statsTotalCoinsLabel = new Text("stats_coins"));
    m_textList.push_back(m_statsTotalGamesText = new Text("stats_games_number_value"));
    m_textList.push_back(m_statsPerGameCoinsLabel = new Text("stats_per_game_coins"));
    m_textList.push_back(m_statsPerGameCoinsText = new Text("stats_per_game_coins"));
    m_textList.push_back(m_statsPerGameDistanceLabel = new Text("stats_per_game_distance"));
    m_textList.push_back(m_statsPerGameDistanceText = new Text("stats_per_game_distance"));
    m_textList.push_back(m_statsPerGameEnemiesLabel = new Text("stats_per_game_enemies"));
    m_textList.push_back(m_statsPerGameEnemiesText = new Text("stats_per_game_enemies"));

    //=== Settings - about

    m_textList.push_back(m_aboutTitleLabel = new Text("about_title"));
    m_textList.push_back(m_aboutDescriptionLabel = new Text("about_description"));
    m_textList.push_back(m_aboutRepositoryLabel = new Text("about_repository"));
    m_textList.push_back(m_aboutEmailLabel = new Text("about_email"));
    m_textList.push_back(m_aboutCopyrightLabel = new Text("about_copyright"));

    //=== Game

    m_textList.push_back(m_currentDistanceText = new Text("game_current_distance"));
    m_textList.push_back(m_playerLifeLabel = new Text("game_player_life"));
    m_textList.push_back(m_bonusTimeoutText = new Text("game_bonus_timeout_value"));
    m_textList.push_back(m_currentCoinsNbText = new Text("game_current_coins_value"));

    //=== Game End

    m_textList.push_back(m_endTitleLabel = new Text("end_title"));
    m_textList.push_back(m_speedMultiplierLabel = new Text("end_speed_multiplier"));
    m_textList.push_back(m_speedMultiplierText = new Text("end_speed_multiplier_value"));
    m_textList.push_back(m_currentDistanceLabel = new Text("end_current_distance"));
    m_textList.push_back(m_coinsCollectedLabel = new Text("end_coins_collected"));
    m_textList.push_back(m_flattenedEnemiesLabel = new Text("end_enemies"));
    m_textList.push_back(m_flattenedEnemiesText = new Text("end_enemies_value"));
    m_textList.push_back(m_currentScoreLabel = new Text("end_score"));
    m_textList.push_back(m_currentScoreText = new Text("end_score_value"));

    updateWholeText();
}


/**
 * Changes Language
 * @author Arthur
 * @date 13/04/16 - 27/10/17
 */
void TextHandler::updateWholeText()
{
    for (Text* t : m_textList)
    {
        t->setCharacterSize(DEFAULT_CHAR_SIZE);
        t->setFont(m_condensedFont);
        t->setFillColor(sf::Color::White);
        std::string utf8_string = m_dataBase->getTextValueFromStringsFile(t->getDescription());
        t->setString(sf::String::fromUtf8(utf8_string.begin(), utf8_string.end()));
    }
}


/**
 * Menu Home Text Syncing
 * @author Arthur
 * @date 02/04/16 - 23/12/16
 */
void TextHandler::syncMenuHomeText()
{}


/**
 * Menu Settings Text Syncing
 * @author Arthur
 * @date 14/04/16 - 27/10/17
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
        m_aboutRepositoryLabel->setPosition(70, 260);
        m_aboutRepositoryLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_aboutEmailLabel->setPosition(70, 350);
        m_aboutEmailLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_aboutCopyrightLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_aboutCopyrightLabel->setPositionSelfCentered(m_width/2, 490);
    }
}


/**
 * Menu Leaderboard Text Syncing
 * @author Arthur
 * @date 19/04/16 - 30/01/17
 */
void TextHandler::syncMenuLeaderboardText()
{
    string scoresEasy = m_dataBase->loadLeaderboardStringFromArray(EASY);
    string scoresHard = m_dataBase->loadLeaderboardStringFromArray(HARD);

    if (scoresEasy.empty())
    {
        updateWholeText();
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
        updateWholeText();
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
 * Menu Shop Text Syncing
 * @author Arthur
 * @date 16/05/16 - 07/01/17
 */
void TextHandler::syncShopText()
{
    m_walletText->setPosition(m_width/2, TITLE_TEXT_X);
    m_walletText->setTextFont(m_condensedFont, DEFAULT_CHAR_SIZE, GOLD_COLOR);
    m_walletText->setStringFromInt(m_dataBase->getWallet());
}


/**
 * Game Screen Syncing
 * @author Arthur
 * @date 02/04/16 - 27/10/17
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
 */
void TextHandler::syncEndText(int gameSpeed)
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

    m_walletText->setTextFont(m_condensedFont, DEFAULT_CHAR_SIZE, GOLD_COLOR);
    m_walletText->setPosition(m_width/2-15, 535);
    m_walletText->setStringFromInt(m_dataBase->getWallet());
}



/**
 * Settings Screen Drawing
 * @author Arthur
 * @date 14/04/16 - 30/01/17
 */
void TextHandler::drawMenuSettingsText(sf::RenderWindow *window, int currentPage) const
{
    switch(currentPage)
    {
        case CONFIG:
            for (auto text : m_textList)
                if (text->getDescription().find("config") != string::npos)
                    text->draw(window);
            break;
        case STATS:
            for (auto text : m_textList)
                if (text->getDescription().find("stats") != string::npos)
                    text->draw(window);
            break;
        case ABOUT:
            for (auto text : m_textList)
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
 */
void TextHandler::drawLeaderboardText(sf::RenderWindow *window) const
{
    for (auto text : m_textList)
        if (text->getDescription().find("leaderboard") != string::npos)
            text->draw(window);
}


/**
 * Shop Screen Drawing
 * @author Arthur
 * @date 16/05/16 - 04/01/17
 */
void TextHandler::drawMenuShopText(sf::RenderWindow *window) const
{
    m_walletText->draw(window);
}


/**
 * Game Screen Drawing
 * @author Arthur
 * @date 02/04/16 - 02/01/17
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
 */
void TextHandler::drawEndText(sf::RenderWindow *window) const
{
    for (auto text : m_textList)
        if (text->getDescription().find("end") != string::npos)
            text->draw(window);

    m_currentDistanceText->draw(window);
    m_currentCoinsNbText->draw(window);
    m_walletText->draw(window);
}
