#include "TextHandler.h"

using namespace std;

/**
 * Constructs a text handler with
 * app's database and size
 * @author Arthur
 * @date 02/04/16 - 07/01/17
 */
TextHandler::TextHandler(DataBase *dataBase, const int width, const int height)
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
 * @date 2/04/16 - 07/01/17
 */
TextHandler::~TextHandler()
{
    for ( Text *t : m_textList)
        delete t;
}


//=== Getters

const sf::Font& TextHandler::getRegularFont() const { return m_regularFont; }
const sf::Font& TextHandler::getCondensedFont() const { return m_condensedFont; }
const sf::Font& TextHandler::getBoldFont() const { return m_BoldFont; }

/**
 * Text Loading
 * @author Arthur
 * @date 02/04/16 - 25/01/17
 * */
void TextHandler::loadText()
{
    //=== Leaderboard

    m_leaderboardTitleLabel = new Text("leaderboard_title");
    m_textList.push_back(m_leaderboardTitleLabel);

    m_leaderboardContentEasyText = new Text("leaderboard_content");
    m_textList.push_back(m_leaderboardContentEasyText);

    m_leaderboardContentHardText = new Text("leaderboard_content");
    m_textList.push_back(m_leaderboardContentHardText);

    //=== Shop

    m_walletText = new Text("wallet");
    m_textList.push_back(m_walletText);


    //=== Settings - configuration

    m_configTitleLabel = new Text("config_title");
    m_textList.push_back(m_configTitleLabel);

    m_configLangTitleLabel = new Text("config_lang_title");
    m_textList.push_back(m_configLangTitleLabel);

    m_configDifficultyTitleLabel = new Text("config_difficulty_title");
    m_textList.push_back(m_configDifficultyTitleLabel);

    m_configCustomTitleLabel = new Text("config_custom_title");
    m_textList.push_back(m_configCustomTitleLabel);

    m_configMusicTitleLabel = new Text("config_music_title");
    m_textList.push_back(m_configMusicTitleLabel);

    //=== Settings - stats

    m_statsTitleLabel = new Text("stats_title");
    m_textList.push_back(m_statsTitleLabel);

    m_statsOverallTitleLabel = new Text("stats_overall_title");
    m_textList.push_back(m_statsOverallTitleLabel);

    m_statsPerGameTitleLabel = new Text("stats_per_game_title");
    m_textList.push_back(m_statsPerGameTitleLabel);

    m_statsTotalDistanceLabel = new Text("stats_distance");
    m_textList.push_back(m_statsTotalDistanceLabel);

    m_statsTotalCoinsNbText = new Text("stats_coins_value");
    m_textList.push_back(m_statsTotalCoinsNbText);

    m_statsTotalDistanceText = new Text("stats_distance");
    m_textList.push_back(m_statsTotalDistanceText);

    m_statsTotalEnemiesLabel = new Text("stats_enemies");
    m_textList.push_back(m_statsTotalEnemiesLabel);

    m_statsTotalGamesLabel = new Text("stats_games_number");
    m_textList.push_back(m_statsTotalGamesLabel);

    m_statsTotalEnemiesText = new Text("stats_enemies_value");
    m_textList.push_back(m_statsTotalEnemiesText);

    m_statsTotalCoinsLabel = new Text("stats_coins");
    m_textList.push_back(m_statsTotalCoinsLabel);

    m_statsTotalGamesText = new Text("stats_games_number_value");
    m_textList.push_back(m_statsTotalGamesText);

    m_statsPerGameCoinsLabel = new Text("stats_per_game_coins");
    m_textList.push_back(m_statsPerGameCoinsLabel);

    m_statsPerGameCoinsText = new Text("stats_per_game_coins");
    m_textList.push_back(m_statsPerGameCoinsText);

    m_statsPerGameDistanceLabel = new Text("stats_per_game_distance");
    m_textList.push_back(m_statsPerGameDistanceLabel);

    m_statsPerGameDistanceText = new Text("stats_per_game_distance");
    m_textList.push_back(m_statsPerGameDistanceText);

    m_statsPerGameEnemiesLabel= new Text("stats_per_game_enemies");
    m_textList.push_back(m_statsPerGameEnemiesLabel);

    m_statsPerGameEnemiesText = new Text("stats_per_game_enemies");
    m_textList.push_back(m_statsPerGameEnemiesText);

    //=== Settings - about

    m_aboutTitleLabel= new Text("about_title");
    m_textList.push_back(m_aboutTitleLabel);

    m_aboutDescriptionLabel = new Text("about_description");
    m_textList.push_back(m_aboutDescriptionLabel);

    m_aboutRepositoryLabel = new Text("about_repository");
    m_textList.push_back(m_aboutRepositoryLabel);

    m_aboutEmailLabel = new Text("about_email");
    m_textList.push_back(m_aboutEmailLabel);

    m_aboutCopyrightLabel = new Text("about_copyright");
    m_textList.push_back(m_aboutCopyrightLabel);


    //=== Game

    m_currentDistanceText = new Text("game_current_distance");
    m_textList.push_back(m_currentDistanceText);

    m_playerLifeLabel = new Text("game_player_life");
    m_textList.push_back(m_playerLifeLabel);

    m_bonusTimeoutText = new Text("game_bonus_timeout_value");
    m_textList.push_back(m_bonusTimeoutText);

    m_currentCoinsNbText = new Text("game_current_coins_value");
    m_textList.push_back(m_currentCoinsNbText);


    //=== Game End

    m_endTitleLabel = new Text("end_title");
    m_textList.push_back(m_endTitleLabel);

    m_speedMultiplierLabel = new Text("end_speed_multiplier");
    m_textList.push_back(m_speedMultiplierLabel);

    m_speedMultiplierText = new Text("end_speed_multiplier_value");
    m_textList.push_back(m_speedMultiplierText);

    m_currentDistanceLabel = new Text("end_current_distance");
    m_textList.push_back(m_currentDistanceLabel);

    m_coinsCollectedLabel = new Text("end_coins_collected");
    m_textList.push_back(m_coinsCollectedLabel);

    m_flattenedEnemiesLabel = new Text("end_enemies");
    m_textList.push_back(m_flattenedEnemiesLabel);

    m_flattenedEnemiesText = new Text("end_enemies_value");
    m_textList.push_back(m_flattenedEnemiesText);

    m_currentScoreLabel = new Text("end_score");
    m_textList.push_back(m_currentScoreLabel);

    m_currentScoreText = new Text("end_score_value");
    m_textList.push_back(m_currentScoreText);

    updateWholeText();
}


/**
 * Changes Language
 * @author Arthur
 * @date 13/04/16 - 25/01/17
 */
void TextHandler::updateWholeText()
{
    for ( Text* t : m_textList)
    {
        t->setCharacterSize(DEFAULT_CHAR_SIZE);
        t->setFont(m_condensedFont);
        t->setColor(sf::Color::White);
        std::string utf8_string = m_dataBase->getStringFromFile(t->getDescription());
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
 * @date 14/04/16 - 25/01/17
 */
void TextHandler::syncSettingsText(int currentPage)
{
    if ( currentPage == CONFIG)
    {
        m_configTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
        m_configLangTitleLabel->setPosition(40, 150);
        m_configDifficultyTitleLabel->setPosition(40, 370);
        m_configCustomTitleLabel->setPosition(m_width/2+40, 150);
        m_configMusicTitleLabel->setPosition(m_width/2 +40, 370);
    }
    else if ( currentPage == STATS)
    {
        m_statsTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
        m_statsOverallTitleLabel->setPosition(40, 130);
        m_statsPerGameTitleLabel->setPosition(m_width/2 + 40, 130);

        m_statsTotalDistanceLabel->setPosition(STAT_LABEL_X, 190);
        m_statsTotalDistanceLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalDistanceText->setPosition(STAT_LABEL_X+250, 190);
        m_statsTotalDistanceText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalDistanceText->setString(to_string( m_dataBase->getTotalDistance() ) + " m" );

        m_statsTotalEnemiesLabel->setPosition(STAT_LABEL_X, 230);
        m_statsTotalEnemiesLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalEnemiesText->setPosition(STAT_LABEL_X+250, 230);
        m_statsTotalEnemiesText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalEnemiesText->setStringFromInt( m_dataBase->getTotalFlattenedEnemies() );

        m_statsTotalCoinsLabel->setPosition(STAT_LABEL_X, 270);
        m_statsTotalCoinsLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalCoinsNbText->setPosition(STAT_LABEL_X+250, 270);
        m_statsTotalCoinsNbText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalCoinsNbText->setColor(sf::Color::White);
        m_statsTotalCoinsNbText->setStringFromInt( m_dataBase->getTotalCoinsNumber() );

        m_statsTotalGamesLabel->setPosition(STAT_LABEL_X, 310);
        m_statsTotalGamesLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalGamesText->setPosition(STAT_LABEL_X+250, 310);
        m_statsTotalGamesText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalGamesText->setStringFromInt( m_dataBase->getTotalGamesPlayed() );

        m_statsPerGameDistanceLabel->setPosition(m_width/2+STAT_LABEL_X, 190);
        m_statsPerGameDistanceLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameDistanceText->setPosition(m_width-2*STAT_LABEL_X, 190);
        m_statsPerGameDistanceText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameDistanceText->setString(to_string( m_dataBase->getPerGameDistance() ) + " m" );

        m_statsPerGameEnemiesLabel->setPosition(m_width/2+STAT_LABEL_X, 230);
        m_statsPerGameEnemiesLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameEnemiesText->setPosition(m_width-2*STAT_LABEL_X, 230);
        m_statsPerGameEnemiesText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameEnemiesText->setStringFromInt( m_dataBase->getPerGameFlattenedEnemies() );

        m_statsPerGameCoinsLabel->setPosition(m_width/2+STAT_LABEL_X, 270);
        m_statsPerGameCoinsLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameCoinsText->setPosition(m_width-2*STAT_LABEL_X, 270);
        m_statsPerGameCoinsText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsPerGameCoinsText->setStringFromInt( m_dataBase->getPerGameCoinsNumber() );
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
 * @date 19/04/16 - 23/01/17
 */
void TextHandler::syncMenuLeaderboardText()
{
    string scoresEasy = "";
    string scoresHard = "";
    m_dataBase->loadStringFromArray(EASY, scoresEasy);
    m_dataBase->loadStringFromArray(HARD, scoresHard);

    if ( scoresEasy.empty() )
    {
        updateWholeText();
        m_leaderboardContentEasyText->setPositionSelfCentered(m_width/4, m_height/2);
    }
    else
    {
        m_leaderboardContentEasyText->setString(scoresEasy);
        m_leaderboardContentEasyText->setCharacterSize(26);
        m_leaderboardContentEasyText->setPositionSelfCentered(m_width/4, 300);
    }

    if ( scoresHard.empty() )
    {
        updateWholeText();
        m_leaderboardContentHardText->setPositionSelfCentered(m_width/2+m_width/4, m_height/2);
    }
    else
    {
        m_leaderboardContentHardText->setString(scoresHard);
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
    m_walletText->setStringFromInt( m_dataBase->getWallet() );
}


/**
 * Game Screen Syncing
 * @author Arthur
 * @date 02/04/16 - 23/12/16
 */
void TextHandler::syncGameText(int bonusTimeout)
{
    m_playerLifeLabel->setPosition(40,545);
    m_currentDistanceLabel->setPosition(440, 545);
    m_currentDistanceText->setPosition(640,545);
    m_currentDistanceText->setColor(sf::Color::White);
    m_currentDistanceText->setString( to_string(
            m_dataBase->getCurrentDistance() ) + " m" );
    m_bonusTimeoutText->setPosition(840,545);
    if ( bonusTimeout > 0) {
        m_bonusTimeoutText->setStringFromInt(bonusTimeout);
        m_bonusTimeoutText->setVisible(true);
    }
    else
        m_bonusTimeoutText->setVisible(false);
}


/**
 * Game Pause Screen Syncing
 * @author Arthur
 * @date 02/04/16 - 23/12/16
 */
void TextHandler::syncPauseText()
{
    m_currentDistanceText->setPosition(PAUSE_TEXT_X, 30);
    m_currentCoinsNbText->setPosition(PAUSE_TEXT_X, 70);
    m_currentCoinsNbText->setColor(GOLD_COLOR);
    m_currentCoinsNbText->setStringFromInt(m_dataBase->getCurrentCoinsNumber() );

    m_flattenedEnemiesText->setPosition(PAUSE_TEXT_X, 110);
    m_flattenedEnemiesText->setColor(ENEMY_BLUE_COLOR);
    m_flattenedEnemiesText->setStringFromInt(m_dataBase->getCurrentFlattenedEnemies() );
}


/**
 * Game End Screen Syncing
 * @author Arthur
 * @date 02/04/16 - 07/01/17
 */
void TextHandler::syncEndText(int gameSpeed)
{
    m_endTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
    m_endTitleLabel->setFont(m_BoldFont);

    m_speedMultiplierLabel->setPosition(SUBTOTAL_LABEL_X, 170);
    m_speedMultiplierText->setPosition(SUBTOTAL_VALUE_X, 170);
    m_speedMultiplierText->setColor(END_GREY_COLOR);
    m_speedMultiplierText->setStringFromInt(gameSpeed);

    m_currentDistanceLabel->setPosition(SUBTOTAL_LABEL_X, 207);
    m_currentDistanceLabel->setColor(sf::Color::White);
    m_currentDistanceText->setPosition(SUBTOTAL_VALUE_X, 207);
    m_currentDistanceText->setColor(END_GREY_COLOR);
    m_currentDistanceText->setString( to_string( m_dataBase->getCurrentDistance() ) + " m" );
    m_currentCoinsNbText->setString( to_string( m_dataBase->getCurrentCoinsNumber() ) + "  X  20" );

    m_coinsCollectedLabel->setPosition(SUBTOTAL_LABEL_X, 245);
    m_currentCoinsNbText->setPosition(SUBTOTAL_VALUE_X, 245);
    m_currentCoinsNbText->setColor(END_GREY_COLOR);
    m_statsTotalCoinsNbText->setStringFromInt( m_dataBase->getTotalCoinsNumber() );

    m_flattenedEnemiesLabel->setPosition(SUBTOTAL_LABEL_X, 290);
    m_flattenedEnemiesLabel->setColor(sf::Color::White);
    m_flattenedEnemiesText->setPosition(SUBTOTAL_VALUE_X, 290);
    m_flattenedEnemiesText->setColor(END_GREY_COLOR);
    m_flattenedEnemiesText->setStringFromInt( m_dataBase->getCurrentFlattenedEnemies() );

    m_currentScoreLabel->setPosition(SUBTOTAL_LABEL_X,350);
    m_currentScoreLabel->setFont(m_BoldFont);
    m_currentScoreText->setPosition(SUBTOTAL_VALUE_X,350);
    m_currentScoreText->setFont(m_BoldFont);
    m_currentScoreText->setStringFromInt( m_dataBase->getCurrentScore() );

    m_walletText->setTextFont(m_condensedFont, DEFAULT_CHAR_SIZE, GOLD_COLOR);
    m_walletText->setPosition(450, 535);
    m_walletText->setStringFromInt( m_dataBase->getWallet() );
}



/**
 * Settings Screen Drawing
 * @author Arthur
 * @date 14/04/16 - 25/01/17
 */
void TextHandler::drawMenuSettingsText(sf::RenderWindow *window, int currentPage) const
{
    if ( currentPage == CONFIG)
    {
        m_configTitleLabel->draw(window);
        m_configLangTitleLabel->draw(window);
        m_configDifficultyTitleLabel->draw(window);
        m_configCustomTitleLabel->draw(window);
        m_configMusicTitleLabel->draw(window);
    }
    else if ( currentPage == STATS)
    {
        m_statsTitleLabel->draw(window);
        m_statsOverallTitleLabel->draw(window);
        m_statsPerGameTitleLabel->draw(window);
        m_statsTotalDistanceLabel->draw(window);
        m_statsTotalEnemiesLabel->draw(window);
        m_statsTotalGamesLabel->draw(window);
        m_statsTotalDistanceText->draw(window);
        m_statsTotalEnemiesText->draw(window);
        m_statsTotalCoinsLabel->draw(window);
        m_statsTotalCoinsNbText->draw(window);
        m_statsTotalGamesText->draw(window);
        m_statsPerGameCoinsLabel->draw(window);
        m_statsPerGameCoinsText->draw(window);
        m_statsPerGameDistanceLabel->draw(window);
        m_statsPerGameDistanceText->draw(window);
        m_statsPerGameEnemiesLabel->draw(window);
        m_statsPerGameEnemiesText->draw(window);
    }
    else //ABOUT
    {
        m_aboutTitleLabel->draw(window);
        m_aboutDescriptionLabel->draw(window);
        m_aboutRepositoryLabel->draw(window);
        m_aboutEmailLabel->draw(window);
        m_aboutCopyrightLabel->draw(window);
    }
}


/**
 * Leaderboard Screen Drawing
 * @author Arthur
 * @date 19/04/16 - 23/01/17
 */
void TextHandler::drawLeaderboardText(sf::RenderWindow *window) const
{
    m_leaderboardTitleLabel->draw(window);
    m_leaderboardContentEasyText->draw(window);
    m_leaderboardContentHardText->draw(window);
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
 * @date 02/04/16 - 04/01/17
 */
void TextHandler::drawEndText(sf::RenderWindow *window) const
{
    m_endTitleLabel->draw(window);
    m_speedMultiplierLabel->draw(window);
    m_speedMultiplierText->draw(window);
    m_currentDistanceLabel->draw(window);
    m_currentDistanceText->draw(window);
    m_coinsCollectedLabel->draw(window);
    m_currentCoinsNbText->draw(window);
    m_flattenedEnemiesLabel->draw(window);
    m_flattenedEnemiesText->draw(window);
    m_currentScoreLabel->draw(window);
    m_currentScoreText->draw(window);
    m_walletText->draw(window);
}
