#include "TextHandler.h"

using namespace std;

/**
 * Default Constructor
 * @author Arthur
 * @date 02/04 - 6/05
 */
TextHandler::TextHandler(DataBase *dataModel, const int width, const int height)
        : m_dataBase{dataModel}, m_width{width}, m_height{height}
{
    m_regularFont = new sf::Font();
    m_regularFont->loadFromFile(ROBOTO_REGULAR_FONT);
    m_condensedFont = new sf::Font();
    m_condensedFont->loadFromFile(ROBOTO_CONDENSED_FONT);
    m_BoldFont = new sf::Font();
    m_BoldFont->loadFromFile(ROBOTO_BOLD_FONT);

    loadText();
}


/**
 * Destructor
 * @author Arthur
 * @date 2/04 - 22/12
 */
TextHandler::~TextHandler()
{
    for ( Text *t : m_textList) delete t;

    delete m_regularFont;
    delete m_condensedFont;
    delete m_BoldFont;
}


//=== Getters

sf::Font* TextHandler::getRegularFont() const { return m_regularFont; }
sf::Font* TextHandler::getCondensedFont() const { return m_condensedFont; }
sf::Font* TextHandler::getBoldFont() const { return m_BoldFont; }
Text* TextHandler::getResumeText() const { return m_pauseResumeLabel; }
Text* TextHandler::getRestartText() const { return m_pauseRestartLabel; }
Text* TextHandler::getHomeText() const { return m_pauseGoToHomeLabel; }

/**
 * Text Loading
 * @author Arthur
 * @date 02/04 - 22/12
 * */
void TextHandler::loadText()
{
    //=== Menu and Leaderboard

    m_menuPlayButtonLabel = new Text("menu_play_button");
    m_textList.push_back(m_menuPlayButtonLabel);

    m_menuQuitButtonLabel = new Text("menu_quit_button");
    m_textList.push_back(m_menuQuitButtonLabel);

    m_leaderboardTitleLabel = new Text("leaderboard_title");
    m_textList.push_back(m_leaderboardTitleLabel);

    m_leaderboardContentText = new Text("leaderboard_content");
    m_textList.push_back(m_leaderboardContentText);

    m_leaderboardClearButtonLabel = new Text("leaderboard_clear_button");
    m_textList.push_back(m_leaderboardClearButtonLabel);


    //=== Settings - configuration

    m_configTitleLabel = new Text("config_title");
    m_textList.push_back(m_configTitleLabel);

    m_configLangTitleLabel = new Text("config_lang_title");
    m_textList.push_back(m_configLangTitleLabel);

    m_configLangEngLabel = new Text("config_lang_english");
    m_textList.push_back(m_configLangEngLabel);

    m_configLangFraLabel = new Text("config_lang_french");
    m_textList.push_back(m_configLangFraLabel);

    m_configLangEspLabel = new Text("config_lang_spanish");
    m_textList.push_back(m_configLangEspLabel);

    m_configDifficultyTitleLabel = new Text("config_difficulty_title");
    m_textList.push_back(m_configDifficultyTitleLabel);

    m_configEasyModeLabel = new Text("config_easy_mode");
    m_textList.push_back(m_configEasyModeLabel);

    m_configHardModeLabel = new Text("config_hard_mode");
    m_textList.push_back(m_configHardModeLabel);

    m_configCustomTitleLabel = new Text("config_custom_title");
    m_textList.push_back(m_configCustomTitleLabel);

    m_configDefaultBallSkinLabel = new Text("config_ball_default_skin");
    m_textList.push_back(m_configDefaultBallSkinLabel);

    m_configMorphBallSkinLabel = new Text("config_ball_morph_skin");
    m_textList.push_back(m_configMorphBallSkinLabel);

    m_configCapsuleBallSkinLabel = new Text("config_ball_capsule_skin");
    m_textList.push_back(m_configCapsuleBallSkinLabel);

    //=== Settings - stats

    m_statsTitleLabel = new Text("stats_title");
    m_textList.push_back(m_statsTitleLabel);

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

    m_statsTotalGamesText = new Text("stats_games_number_value");
    m_textList.push_back(m_statsTotalGamesText);

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

    //=== Shop

    m_shopDialogTitleLabel = new Text("shop_dialog_title");
    m_textList.push_back(m_shopDialogTitleLabel);

    m_shopDialogContentLabel = new Text("shop_dialog_content");
    m_textList.push_back(m_shopDialogContentLabel);

    m_shopDialogNegativeLabel = new Text("shop_dialog_cancel");
    m_textList.push_back(m_shopDialogNegativeLabel);

    m_shopDialogPositiveLabel = new Text("shop_dialog_ok");
    m_textList.push_back(m_shopDialogPositiveLabel);

    m_shopBuySuccessfulLabel = new Text("shop_dialog_success");
    m_textList.push_back(m_shopBuySuccessfulLabel);

    m_shopBuyUnsuccessfulLabel = new Text("shop_dialog_failure");
    m_textList.push_back(m_shopBuyUnsuccessfulLabel);


    //=== Game

    m_currentDistanceText = new Text("game_current_distance");
    m_textList.push_back(m_currentDistanceText);

    m_playerLifeLabel = new Text("game_player_life");
    m_textList.push_back(m_playerLifeLabel);

    m_bonusTimeoutText = new Text("game_bonus_timeout_value");
    m_textList.push_back(m_bonusTimeoutText);

    m_currentCoinsNbText = new Text("game_current_coins_value");
    m_textList.push_back(m_currentCoinsNbText);


    //=== Pause

    m_pauseResumeLabel = new Text("pause_resume");
    m_textList.push_back(m_pauseResumeLabel);

    m_pauseRestartLabel = new Text("pause_restart");
    m_textList.push_back(m_pauseRestartLabel);

    m_pauseGoToHomeLabel = new Text("pause_go_to_home");
    m_textList.push_back(m_pauseGoToHomeLabel);


    //=== End

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

    m_saveButtonText = new Text("end_save_button");
    m_textList.push_back(m_saveButtonText);

    updateWholeText();
}


/**
 * Change Language
 * @author Arthur
 * @date 13/04 - 22/12
 */
void TextHandler::updateWholeText()
{
    for ( Text* t : m_textList)
    {
        t->setCharacterSize(DEFAULT_CHAR_SIZE);
        t->setFont(*m_condensedFont);
        t->setColor(sf::Color::White);

        if ( m_dataBase->getLanguage() == "en")
        {
            updateString(ENGLISH_STRINGS, t);
        }
        else if ( m_dataBase->getLanguage() == "fr")
        {
            updateString(FRENCH_STRINGS, t);
        }
        else if ( m_dataBase->getLanguage() == "es")
        {
            updateString(SPANISH_STRINGS, t);
        }
    }
}


/**
 * Update text string
 * @author Arthur
 * @date 13/04 - 22/12
 */
void TextHandler::updateString(string file, Text *text)
{
    pugi::xml_document doc;
    doc.load_file(file.c_str());

    pugi::xml_node resources = doc.child("resources");

    for (pugi::xml_node item: resources.children("string"))
    {
        if (string(item.attribute("name").value()) == text->getDescription())
        {
            text->setString(item.attribute("value").value());
            break;
        }
    }
}


/**
 * Menu Home Text Syncing
 * @author Arthur
 * @date 02/04 - 22/12
 */
void TextHandler::syncMenuHomeText()
{
    m_menuPlayButtonLabel->setPositionSelfCentered( m_width/2, m_height/1.42 );
    m_menuQuitButtonLabel->setPositionSelfCentered( m_width/2, m_height/1.15 );
}


/**
 * Menu Settings Text Syncing
 * @author Arthur
 * @date 14/04 - 22/12
 */
void TextHandler::syncSettingsText(int currentPage)
{
    if ( currentPage == CONFIG)
    {
        m_configTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
        m_configLangTitleLabel->setPosition(40, 150);
        m_configLangEngLabel->setPosition(RADIO_TEXT_X, 202);
        m_configLangFraLabel->setPosition(RADIO_TEXT_X, 242);
        m_configLangEspLabel->setPosition(RADIO_TEXT_X, 282);
        m_configDifficultyTitleLabel->setPosition(40, 370);
        m_configEasyModeLabel->setPosition(RADIO_TEXT_X, 417);
        m_configHardModeLabel->setPosition(RADIO_TEXT_X, 457);
        m_configCustomTitleLabel->setPosition(m_width/2 + 40, 150);
        m_configDefaultBallSkinLabel->setPosition(m_width/2 + RADIO_TEXT_X, 202);
        m_configMorphBallSkinLabel->setPosition(m_width/2 + RADIO_TEXT_X, 242);
        m_configCapsuleBallSkinLabel->setPosition(m_width/2 + RADIO_TEXT_X, 282);
    }
    else if ( currentPage == STATS)
    {
        m_statsTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
        m_statsTotalDistanceLabel->setPosition(RADIO_TEXT_X, 150);
        m_statsTotalDistanceLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalEnemiesLabel->setPosition(RADIO_TEXT_X, 190);
        m_statsTotalEnemiesLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalGamesLabel->setPosition(RADIO_TEXT_X, 230);
        m_statsTotalGamesLabel->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalDistanceText->setPosition(m_width/2, 150);
        m_statsTotalEnemiesText->setPosition(m_width/2, 190);
        m_statsTotalGamesText->setPosition(m_width/2, 230);

        m_statsTotalDistanceText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalDistanceText->setString(to_string( m_dataBase->getTotalDistance() ) + " m" );
        m_statsTotalEnemiesText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalEnemiesText->setStringFromInt( m_dataBase->getTotalFlattenedEnemies() );
        m_statsTotalGamesText->setCharacterSize(CONTENT_CHAR_SIZE);
        m_statsTotalGamesText->setStringFromInt( m_dataBase->getTotalGamesPlayed() );
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
 * @date 19/04 - 22/12
 */
void TextHandler::syncMenuLeaderboardText()
{
    string scores = "";
    m_dataBase->loadStringFromArray(scores);

    if ( scores.empty() )
    {
        m_leaderboardContentText->setDescription("leaderboard_content");
        updateWholeText();
        m_leaderboardContentText->setPositionSelfCentered(m_width/2, 250);
    }
    else
    {
        m_leaderboardContentText->setDescription("leaderboard_content");
        m_leaderboardContentText->setString(scores);
        m_leaderboardContentText->setCharacterSize(30);
        m_leaderboardContentText->setPositionSelfCentered(m_width/2, 100);
    }

    m_leaderboardTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);

    m_leaderboardClearButtonLabel->setCharacterSize(20);
    m_leaderboardClearButtonLabel->setPositionSelfCentered(m_width/2, 547);
}


/**
 * Menu Shop Text Syncing
 * @author Arthur
 * @date 16/05
 */
void TextHandler::syncShopText()
{
    m_statsTotalCoinsNbText->setPosition(m_width/2, TITLE_TEXT_X);
    m_statsTotalCoinsNbText->setColor(GOLD_COLOR);

    m_statsTotalCoinsNbText->setString( to_string( m_dataBase->getTotalCoinsNumber() ));
}


/**
 * Shop Dialog Sync
 * @author Arthur
 * @date 17/04
 */
void TextHandler::syncDialogText(string context, string &title, string &content, string &neg_choice, string &pos_choice)
{
    //TODO : put instead dialog object in parameter
    if ( context == "askBuying")
    {
        title = m_shopDialogTitleLabel->getString();
        content = m_shopDialogContentLabel->getString();
        neg_choice = m_shopDialogNegativeLabel->getString();
        pos_choice = m_shopDialogPositiveLabel->getString();
    }
    else if  ( context == "success")
    {
        title = "";
        content = m_shopBuySuccessfulLabel->getString();
        neg_choice = "";
        pos_choice = m_shopDialogPositiveLabel->getString();
    }
    else if  ( context == "failure")
    {
        title = "";
        content = m_shopBuyUnsuccessfulLabel->getString();
        neg_choice = "";
        pos_choice = m_shopDialogPositiveLabel->getString();
    }
}


/**
 * Game Screen Syncing
 * @author Arthur
 * @date 02/04 - 17/04
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
    if ( bonusTimeout > 0)
        m_bonusTimeoutText->setStringFromInt(bonusTimeout);
    else
        m_bonusTimeoutText->setString("");
}


/**
 * Game Pause Screen Syncing
 * @author Arthur
 * @date 02/04 - 7/05
 */
void TextHandler::syncPauseText()
{
    m_currentDistanceText->setPosition(PAUSE_TEXT_X, 30);
    m_currentCoinsNbText->setPosition(PAUSE_TEXT_X, 70);
    m_currentCoinsNbText->setColor(GOLD_COLOR);
    m_flattenedEnemiesText->setPosition(PAUSE_TEXT_X, 110);
    m_flattenedEnemiesText->setColor(ENEMY_BLUE_COLOR);
    m_pauseResumeLabel->setPosition(PAUSE_TEXT_X, 350);
    m_pauseRestartLabel->setPosition(PAUSE_TEXT_X, 400);
    m_pauseGoToHomeLabel->setPosition(PAUSE_TEXT_X, 450);

    m_currentCoinsNbText->setStringFromInt(m_dataBase->getCurrentCoinsNumber() );
    m_flattenedEnemiesText->setStringFromInt(m_dataBase->getCurrentFlattenedEnemies() );
}

/**
 * Game End Screen Syncing
 * @author Arthur
 * @date 02/04 - 22/12
 */
void TextHandler::syncEndText(bool isGameSaved, int gameSpeed)
{
    //=== Score sub-total text
    m_endTitleLabel->setPositionSelfCentered(m_width/2, TITLE_TEXT_X);
    m_endTitleLabel->setFont(*m_BoldFont);

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
    m_currentScoreLabel->setFont(*m_BoldFont);
    m_currentScoreText->setPosition(SUBTOTAL_VALUE_X,350);
    m_currentScoreText->setFont(*m_BoldFont);
    m_currentScoreText->setStringFromInt( m_dataBase->getCurrentScore() );

    m_saveButtonText->setCharacterSize(20);
    if (!isGameSaved)  //TODO : Button class with visibility
    {
        m_saveButtonText->setPosition(-100, -100);
    }
    else {
        m_saveButtonText->setPositionSelfCentered(m_width/2, 437);
    }

    //=== Bottom bar text
    m_pauseGoToHomeLabel->setPosition(80,535);
    m_statsTotalCoinsNbText->setPositionSelfCentered(450, 535);
    m_statsTotalCoinsNbText->setColor(GOLD_COLOR);
    m_pauseRestartLabel->setPositionSelfCentered(760, 535);
}


/**
 * Menu Home Screen Drawing
 * @author Arthur
 * @date 02/04 - 13/04
 */
void TextHandler::drawMenuHomeText(sf::RenderWindow *window) const
{
    window->draw(*m_menuPlayButtonLabel);
    window->draw(*m_menuQuitButtonLabel);
}


/**
 * Settings Screen Drawing
 * @author Arthur
 * @date 14/04 - 22/12
 */
void TextHandler::drawMenuSettingsText(sf::RenderWindow *window, int currentPage) const
{
    if ( currentPage == CONFIG)
    {
        window->draw(*m_configTitleLabel);
        window->draw(*m_configLangTitleLabel);
        window->draw(*m_configLangEngLabel);
        window->draw(*m_configLangFraLabel);
        window->draw(*m_configLangEspLabel);
        window->draw(*m_configDifficultyTitleLabel);
        window->draw(*m_configEasyModeLabel);
        window->draw(*m_configHardModeLabel);
        window->draw(*m_configCustomTitleLabel);
        window->draw(*m_configDefaultBallSkinLabel);
        window->draw(*m_configMorphBallSkinLabel);
        window->draw(*m_configCapsuleBallSkinLabel);
    }
    else if ( currentPage == STATS)
    {
        window->draw(*m_statsTitleLabel);
        window->draw(*m_statsTotalDistanceLabel);
        window->draw(*m_statsTotalEnemiesLabel);
        window->draw(*m_statsTotalGamesLabel);
        window->draw(*m_statsTotalDistanceText);
        window->draw(*m_statsTotalEnemiesText);
        window->draw(*m_statsTotalGamesText);
    }
    else //ABOUT
    {
        window->draw(*m_aboutTitleLabel);
        window->draw(*m_aboutDescriptionLabel);
        window->draw(*m_aboutRepositoryLabel);
        window->draw(*m_aboutEmailLabel);
        window->draw(*m_aboutCopyrightLabel);
    }
}


/**
 * Leaderboard Screen Drawing
 * @author Arthur
 * @date 19/04 - 20/04
 */
void TextHandler::drawLeaderboardText(sf::RenderWindow *window) const
{
    window->draw(*m_leaderboardTitleLabel);
    window->draw(*m_leaderboardContentText);
    window->draw(*m_leaderboardClearButtonLabel);
}


/**
 * Shop Screen Drawing
 * @author Arthur
 * @date 16/05
 */
void TextHandler::drawMenuShopText(sf::RenderWindow *window) const
{
    window->draw(*m_statsTotalCoinsNbText);
}


/**
 * Game Screen Drawing
 * @author Arthur
 * @date 02/04 - 17/04
 */
void TextHandler::drawGameText(sf::RenderWindow *window) const
{
    window->draw(*m_playerLifeLabel);
    window->draw(*m_currentDistanceLabel);
    window->draw(*m_currentDistanceText);
    window->draw(*m_bonusTimeoutText);
}


/**
 * Pause Screen Drawing
 * @author Arthur
 * @date 02/04 - 17/04
 */
void TextHandler::drawPauseText(sf::RenderWindow *window) const
{
    window->draw(*m_currentDistanceText);
    window->draw(*m_currentCoinsNbText);
    window->draw(*m_flattenedEnemiesText);
    window->draw(*m_pauseResumeLabel);
    window->draw(*m_pauseRestartLabel);
    window->draw(*m_pauseGoToHomeLabel);
}


/**
 * End Screen Drawing
 * @author Arthur
 * @date 02/04 - 3/05
 */
void TextHandler::drawEndText(sf::RenderWindow *window) const
{
    window->draw(*m_endTitleLabel);
    window->draw(*m_speedMultiplierLabel);
    window->draw(*m_speedMultiplierText);
    window->draw(*m_currentDistanceLabel);
    window->draw(*m_currentDistanceText);
    window->draw(*m_coinsCollectedLabel);
    window->draw(*m_currentCoinsNbText);
    window->draw(*m_flattenedEnemiesLabel);
    window->draw(*m_flattenedEnemiesText);
    window->draw(*m_currentScoreLabel);
    window->draw(*m_currentScoreText);
    window->draw(*m_saveButtonText);
    window->draw(*m_pauseGoToHomeLabel);
    window->draw(*m_statsTotalCoinsNbText);
    window->draw(*m_pauseRestartLabel);
}
