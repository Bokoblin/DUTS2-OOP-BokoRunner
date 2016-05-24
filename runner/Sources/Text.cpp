#include "Text.h"

using namespace std;

/********************************************
    Default Constructor
*********************************************
    @author Arthur  @date 02/04 - 6/05
*********************************************/
Text::Text(DataBase *dataModel) : m_dataBase{dataModel}
{
    m_regularFont = new sf::Font();
    m_regularFont->loadFromFile(ROBOTO_REGULAR_FONT);
    m_condensedFont = new sf::Font();
    m_condensedFont->loadFromFile(ROBOTO_CONDENSED_FONT);
    m_BoldFont = new sf::Font();
    m_BoldFont->loadFromFile(ROBOTO_BOLD_FONT);

    loadText();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 2/04 - 20/05
*********************************************/
Text::~Text()
{
    for ( map<sf::Text*, string>::iterator it = m_textMap.begin();
        it !=m_textMap.end(); ++it) delete it->first;

    delete m_regularFont;
    delete m_condensedFont;
    delete m_BoldFont;
}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 02/04 - 20/05
*********************************************/
sf::Font* Text::getRegularFont() const { return m_regularFont; }
sf::Font* Text::getCondensedFont() const { return m_condensedFont; }
sf::Font* Text::getBoldFont() const { return m_BoldFont; }
sf::Text* Text::getResumeText() const { return m_pauseResumeLabel; }
sf::Text* Text::getRestartText() const { return m_pauseRestartLabel; }
sf::Text* Text::getHomeText() const { return m_pauseGoToHomeLabel; }

/********************************************
    Text Loading
*********************************************
    @author Arthur  @date 02/04 - 6/05
*********************************************/
void Text::loadText()
{
    m_playButtonLabel = new sf::Text;
    m_textMap[m_playButtonLabel] = "playButtonLabel";

    m_quitButtonLabel = new sf::Text;
    m_textMap[m_quitButtonLabel] = "quitButtonLabel";

    m_configTitleLabel = new sf::Text;
    m_textMap[m_configTitleLabel] = "configTitleLabel";

    m_configLangTitleLabel = new sf::Text;
    m_textMap[m_configLangTitleLabel] = "configLangTitleLabel";

    m_configLangEngLabel = new sf::Text;
    m_textMap[m_configLangEngLabel] = "configLangEngLabel";

    m_configLangFraLabel = new sf::Text;
    m_textMap[m_configLangFraLabel] = "configLangFraLabel";

    m_configLangEspLabel = new sf::Text;
    m_textMap[m_configLangEspLabel] = "configLangEspLabel";

    m_configDifficultyTitleLabel = new sf::Text;
    m_textMap[m_configDifficultyTitleLabel] = "configDifficultyLabel";

    m_configDifficultyNormalLabel = new sf::Text;
    m_textMap[m_configDifficultyNormalLabel] = "configDifficultyNormalLabel";

    m_configDifficultyMasterLabel = new sf::Text;
    m_textMap[m_configDifficultyMasterLabel] = "configDifficultyMasterLabel";

    m_configCustomTitleLabel = new sf::Text;
    m_textMap[m_configCustomTitleLabel] = "configCustomTitleLabel";

    m_configDefaultBallskinLabel = new sf::Text;
    m_textMap[m_configDefaultBallskinLabel] = "configDefaultBallskinLabel";

    m_configMorphBallskinLabel = new sf::Text;
    m_textMap[m_configMorphBallskinLabel] = "configMorphBallskinLabel";

    m_configCapsuleBallskinLabel = new sf::Text;
    m_textMap[m_configCapsuleBallskinLabel] = "configCapsuleBallskinLabel";

    m_statisticsTitleLabel = new sf::Text;
    m_textMap[m_statisticsTitleLabel] = "statisticsTitleLabel";

    m_totalDistanceLabel = new sf::Text;
    m_textMap[m_totalDistanceLabel] = "totalDistanceLabel";

    m_totalCoinsNbText = new sf::Text;
    m_textMap[m_totalCoinsNbText] = "totalCoinsText";

    m_totalFlattenedEnemiesLabel = new sf::Text;
    m_textMap[m_totalFlattenedEnemiesLabel] = "totalFlattenedEnemiesLabel";

    m_totalGamesPlayedLabel = new sf::Text;
    m_textMap[m_totalGamesPlayedLabel] = "totalGamesPlayedLabel";

    m_totalDistanceText = new sf::Text;
    m_textMap[m_totalDistanceText] = "totalDistanceText";

    m_totalFlattenedEnemiesText = new sf::Text;
    m_textMap[m_totalFlattenedEnemiesText] = "totalEnemiesDestructedText";

    m_totalGamesPlayedText = new sf::Text;
    m_textMap[m_totalGamesPlayedText] = "totalGamesPlayedText";

    m_creditsTitleLabel= new sf::Text;
    m_textMap[m_creditsTitleLabel] = "creditsTitleLabel";

    m_creditsContentLabel = new sf::Text;
    m_textMap[m_creditsContentLabel] = "creditsContentLabel";

    m_copyrightLabel = new sf::Text;
    m_textMap[m_copyrightLabel] = "copyrightLabel";

    m_shopDialogTitleLabel = new sf::Text;
    m_textMap[m_shopDialogTitleLabel] = "shopDialogTitleLabel";

    m_shopDialogContentLabel = new sf::Text;
    m_textMap[m_shopDialogContentLabel] = "shopDialogContentLabel";

    m_shopDialogNegativeLabel = new sf::Text;
    m_textMap[m_shopDialogNegativeLabel] = "shopDialogNegativeLabel";

    m_shopDialogPositiveLabel = new sf::Text;
    m_textMap[m_shopDialogPositiveLabel] = "shopDialogPositiveLabel";

    m_buySuccessContentLabel = new sf::Text;
    m_textMap[m_buySuccessContentLabel] = "buySuccessContentLabel";

    m_buyFailureContentLabel = new sf::Text;
    m_textMap[m_buyFailureContentLabel] = "buyFailureContentLabel";

    m_leaderboardTitleLabel = new sf::Text;
    m_textMap[m_leaderboardTitleLabel] = "leaderboardTitleLabel";

    m_leaderboardContentText = new sf::Text;
    m_textMap[m_leaderboardContentText] = "leaderboardContentText";

    m_clearButtonLabel = new sf::Text;
    m_textMap[m_clearButtonLabel] = "clearButtonLabel";

    m_currentDistanceText = new sf::Text;
    m_textMap[m_currentDistanceText] = "distanceText";

    m_playerLifeLabel = new sf::Text;
    m_textMap[m_playerLifeLabel] = "playerLifeLabel";

    m_bonusTimeoutText = new sf::Text;
    m_textMap[m_bonusTimeoutText] = "bonusTimeoutText";

    m_currentCoinsNbText = new sf::Text;
    m_textMap[m_currentCoinsNbText] = "coinsCollectedNumberText";

    m_pauseResumeLabel = new sf::Text;
    m_textMap[m_pauseResumeLabel] = "pauseResumeLabel";

    m_pauseRestartLabel = new sf::Text;
    m_textMap[m_pauseRestartLabel] = "pauseRestartLabel";

    m_pauseGoToHomeLabel = new sf::Text;
    m_textMap[m_pauseGoToHomeLabel] = "pauseGotoHomeLabel";

    m_endTitleLabel = new sf::Text;
    m_textMap[m_endTitleLabel] = "endTitleLabel";

    m_saveButtonText = new sf::Text;
    m_textMap[m_saveButtonText] = "saveButtonLabel";

    m_speedMultiplierLabel = new sf::Text;
    m_textMap[m_speedMultiplierLabel] = "speedMultiplierLabel";

    m_speedMultiplierText = new sf::Text;
    m_textMap[m_speedMultiplierText] = "speedMultiplierText";

    m_currentDistanceLabel = new sf::Text;
    m_textMap[m_currentDistanceLabel] = "currentDistanceLabel";

    m_coinsCollectedLabel = new sf::Text;
    m_textMap[m_coinsCollectedLabel] = "coinsCollectedLabel";

    m_flattenedEnemiesLabel = new sf::Text;
    m_textMap[m_flattenedEnemiesLabel] = "flattenedEnemiesLabel";

    m_flattenedEnemiesText = new sf::Text;
    m_textMap[m_flattenedEnemiesText] = "flattenedEnemiesText";

    m_currentScoreLabel = new sf::Text;
    m_textMap[m_currentScoreLabel] = "currentScoreLabel";

    m_currentScoreText = new sf::Text;
    m_textMap[m_currentScoreText] = "currentScoreText";

    updateWholeText();
}


/********************************************
    Change Language
*********************************************
    @author Arthur  @date 13/04 - 6/05
*********************************************/
void Text::updateWholeText()
{
    for ( map<sf::Text*, string>::iterator it = m_textMap.begin();
          it !=m_textMap.end(); ++it)
    {
        it->first->setCharacterSize(DEFAULT_CHARACTER_SIZE);
        it->first->setFont(*m_condensedFont);
        it->first->setColor(sf::Color::White);

        if ( m_dataBase->getLanguage() == "en")
        {
            updateString(ENGLISH_STRINGS, it->first, it->second);
        }
        else if ( m_dataBase->getLanguage() == "fr")
        {
            updateString(FRENCH_STRINGS, it->first, it->second);
        }
        else if ( m_dataBase->getLanguage() == "es")
        {
            updateString(SPANISH_STRINGS, it->first, it->second);
        }
    }
}


/********************************************
    Update text string
*********************************************
    @author Arthur  @date 13/04
*********************************************/
void Text::updateString(string file, sf::Text *text, string name)
{
    fstream f;
    size_t found = string::npos;
    string line="";
    string result="";

    f.open(file.c_str(), ios::in);
    assert( !f.fail() );

    f >> line;
    while( !f.eof() && found == string::npos)
    {
        found=line.find("name=\""+ name + "\"");
        if (found!=std::string::npos)
        {
            int pos = 0;
            while ( line[pos] != '>') pos++;
            pos++;
            while ( line[pos] != '<')
            {
                result += line[pos];
                pos++;
            }
            for (unsigned int i=0; i < result.size(); i++)
                if (result[i] == '_') result[i] = ' ';
        }

        f >> line;
    }

    f.close();
    text->setString(result);
}


/********************************************
    Menu Home Text Syncing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::syncMenuHomeText(int w, int h)
{
    m_playButtonLabel->setPosition( w/2 -
        int(m_playButtonLabel->HALF_WIDTH), h/1.42 );
    m_quitButtonLabel->setPosition( w/2 -
        int(m_quitButtonLabel->HALF_WIDTH), h/1.15 );
}


/********************************************
    Menu Settings Text Syncing
*********************************************
    @author Arthur  @date 14/04 - 20/05
*********************************************/
void Text::syncSettingsText(int w, int h)
{
    //=== Configuration

    m_configTitleLabel->setPosition(w/2 -
        int(m_configTitleLabel->HALF_WIDTH), TITLE_TEXT_ROW);
    m_configLangTitleLabel->setPosition(40, 150);
    m_configLangEngLabel->setPosition(RADIO_TEXT_X, 202);
    m_configLangFraLabel->setPosition(RADIO_TEXT_X, 242);
    m_configLangEspLabel->setPosition(RADIO_TEXT_X, 282);
    m_configDifficultyTitleLabel->setPosition(40, 370);
    m_configDifficultyNormalLabel->setPosition(RADIO_TEXT_X, 417);
    m_configDifficultyMasterLabel->setPosition(RADIO_TEXT_X, 457);
    m_configCustomTitleLabel->setPosition(w/2+40, 150);
    m_configDefaultBallskinLabel->setPosition(w/2+RADIO_TEXT_X, 202);
    m_configMorphBallskinLabel->setPosition(w/2+RADIO_TEXT_X, 242);
    m_configCapsuleBallskinLabel->setPosition(w/2+RADIO_TEXT_X, 282);

    //=== Statistics

    m_statisticsTitleLabel->setPosition(w/2 -
        int(m_statisticsTitleLabel->HALF_WIDTH), TITLE_TEXT_ROW);
    m_totalDistanceLabel->setPosition(RADIO_TEXT_X, 150);
    m_totalDistanceLabel->setCharacterSize(CONTENT_CHARACTER_SIZE);
    m_totalFlattenedEnemiesLabel->setPosition(RADIO_TEXT_X, 190);
    m_totalFlattenedEnemiesLabel->setCharacterSize(CONTENT_CHARACTER_SIZE);
    m_totalGamesPlayedLabel->setPosition(RADIO_TEXT_X, 230);
    m_totalGamesPlayedLabel->setCharacterSize(CONTENT_CHARACTER_SIZE);
    m_totalDistanceText->setPosition(w/2, 150);
    m_totalFlattenedEnemiesText->setPosition(w/2, 190);
    m_totalGamesPlayedText->setPosition(w/2, 230);
    m_creditsTitleLabel->setPosition(w/2 -
        int(m_creditsTitleLabel->HALF_WIDTH), h/2);
    m_creditsContentLabel->setPosition(RADIO_TEXT_X, 400);
    m_creditsContentLabel->setCharacterSize(CONTENT_CHARACTER_SIZE);
    m_copyrightLabel->setCharacterSize(CONTENT_CHARACTER_SIZE);
    m_copyrightLabel->setPosition(w/2 -
        int(m_copyrightLabel->HALF_WIDTH), 490);


    m_totalDistanceText->setCharacterSize(CONTENT_CHARACTER_SIZE);
    m_totalDistanceText->setString(to_string( m_dataBase->getTotalDistance() ) + " m" );
    m_totalFlattenedEnemiesText->setCharacterSize(CONTENT_CHARACTER_SIZE);
    m_totalFlattenedEnemiesText->setString( to_string( m_dataBase->getTotalFlattenedEnemies() ) );
    m_totalGamesPlayedText->setCharacterSize(CONTENT_CHARACTER_SIZE);
    m_totalGamesPlayedText->setString(to_string( m_dataBase->getTotalGamesPlayed() ) );
}


/********************************************
    Menu Leaderboard Text Syncing
*********************************************
    @author Arthur  @date 19/04 - 20/04
*********************************************/
void Text::syncMenuLeaderboardText(int w, int h, Leaderboard* lb)
{
    string scores = "";

    if (lb->checkFileIntegrity() == true)
    {
        lb->loadVectorFromFile();
        lb->loadStringFromVector(scores);
    }
    else
        scores = "corrupted";

    if ( scores == "corrupted" )
    {
        m_textMap[m_leaderboardContentText] = "leaderboardErrorText";
        updateWholeText();
        m_leaderboardContentText->setPosition(w/2 -
            int(m_leaderboardContentText->HALF_WIDTH), 250);
    }
    else if ( scores == "empty")
    {
        m_textMap[m_leaderboardContentText] = "leaderboardText";
        updateWholeText();
        m_leaderboardContentText->setPosition(w/2 -
                int(m_leaderboardContentText->HALF_WIDTH), 250);
    }
    else //valid and not empty
    {
        m_textMap[m_leaderboardContentText] = "leaderboardText";
        m_leaderboardContentText->setString(scores);
        m_leaderboardContentText->setCharacterSize(30);
        m_leaderboardContentText->setPosition(w/2 -
                int(m_leaderboardContentText->HALF_WIDTH), 100);
    }

    m_leaderboardTitleLabel->setPosition(w/2 -
            int(m_leaderboardTitleLabel->HALF_WIDTH), TITLE_TEXT_ROW);

    m_clearButtonLabel->setCharacterSize(20);
    m_clearButtonLabel->setPosition(w/2 -
            int(m_clearButtonLabel->HALF_WIDTH), 547);
}


/********************************************
    Menu Shop Text Syncing
*********************************************
    @author Arthur  @date 16/05 -
*********************************************/
void Text::syncShopText(int w, int h)
{
    m_totalCoinsNbText->setPosition(w/2, TITLE_TEXT_ROW);
    m_totalCoinsNbText->setColor(GOLD_COLOR);

    m_totalCoinsNbText->setString( to_string( m_dataBase->getTotalCoinsNumber() ));
}


/********************************************
    Shop Dialog Sync
*********************************************
    @author Arthur  @date 17/04
*********************************************/
void Text::syncDialogText(string context, string &title, string &content, string &neg_choice, string &pos_choice)
{
    if ( context == "askBying")
    {
        title = m_shopDialogTitleLabel->getString();
        content = m_shopDialogContentLabel->getString();
        neg_choice = m_shopDialogNegativeLabel->getString();
        pos_choice = m_shopDialogPositiveLabel->getString();
    }
    else if  ( context == "success")
    {
        title = "";
        content = m_buySuccessContentLabel->getString();
        neg_choice = "";
        pos_choice = m_shopDialogPositiveLabel->getString();
    }
    else if  ( context == "failure")
    {
        title = "";
        content = m_buyFailureContentLabel->getString();
        neg_choice = "";
        pos_choice = m_shopDialogPositiveLabel->getString();
    }
}


/********************************************
    Game Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 17/04
*********************************************/
void Text::syncGameText(GameModel *gameModel)
{
    m_playerLifeLabel->setPosition(40,545);
    m_currentDistanceLabel->setPosition(440, 545);
    m_currentDistanceText->setPosition(640,545);
    m_currentDistanceText->setColor(sf::Color::White);
    m_currentDistanceText->setString( to_string(
            m_dataBase->getCurrentDistance() ) + " m" );
    m_bonusTimeoutText->setPosition(840,545);
    if ( gameModel->getBonusTimeout() > 0)
        m_bonusTimeoutText->setString( to_string(gameModel->getBonusTimeout() ) );
    else
        m_bonusTimeoutText->setString("");
}


/********************************************
    Game Pause Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 7/05
*********************************************/
void Text::syncPauseText()
{
    m_currentDistanceText->setPosition(PAUSE_TEXT_X, 30);
    m_currentCoinsNbText->setPosition(PAUSE_TEXT_X, 70);
    m_currentCoinsNbText->setColor(GOLD_COLOR);
    m_flattenedEnemiesText->setPosition(PAUSE_TEXT_X, 110);
    m_flattenedEnemiesText->setColor(ENEMY_BLUE_COLOR);
    m_pauseResumeLabel->setPosition(PAUSE_TEXT_X, 350);
    m_pauseRestartLabel->setPosition(PAUSE_TEXT_X, 400);
    m_pauseGoToHomeLabel->setPosition(PAUSE_TEXT_X, 450);

    m_currentCoinsNbText->setString(to_string(
            m_dataBase->getCurrentCoinsNumber() ) );
    m_flattenedEnemiesText->setString(to_string(
            m_dataBase->getCurrentFlattenedEnemies() ) );
}

/********************************************
    Game End Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 20/05
*********************************************/
void Text::syncEndText(GameModel *gameModel, int w, int h)
{
    //=== Score sub-total text
    m_endTitleLabel->setPosition(w/2 - int(m_endTitleLabel->HALF_WIDTH), TITLE_TEXT_ROW);
    m_endTitleLabel->setFont(*m_BoldFont);
    m_speedMultiplierLabel->setPosition(SUBTOTAL_LABEL_X, 170);
    m_speedMultiplierText->setPosition(SUBTOTAL_VALUE_X, 170);
    m_speedMultiplierText->setColor(END_GREY_COLOR);
    m_currentDistanceLabel->setPosition(SUBTOTAL_LABEL_X, 207);
    m_currentDistanceLabel->setColor(sf::Color::White);
    m_currentDistanceText->setPosition(SUBTOTAL_VALUE_X, 207);
    m_currentDistanceText->setColor(END_GREY_COLOR);
    m_coinsCollectedLabel->setPosition(SUBTOTAL_LABEL_X, 245);
    m_currentCoinsNbText->setPosition(SUBTOTAL_VALUE_X, 245);
    m_currentCoinsNbText->setColor(END_GREY_COLOR);
    m_flattenedEnemiesLabel->setPosition(SUBTOTAL_LABEL_X, 290);
    m_flattenedEnemiesLabel->setColor(sf::Color::White);
    m_flattenedEnemiesText->setPosition(SUBTOTAL_VALUE_X, 290);
    m_flattenedEnemiesText->setColor(END_GREY_COLOR);
    m_currentScoreLabel->setPosition(SUBTOTAL_LABEL_X,350);
    m_currentScoreLabel->setFont(*m_BoldFont);
    m_currentScoreText->setPosition(SUBTOTAL_VALUE_X,350);
    m_currentScoreText->setFont(*m_BoldFont);
    m_saveButtonText->setCharacterSize(20);
    if ( gameModel->getSaveStatus() == false)
            m_saveButtonText->setPosition(-100, -100);
    else
        m_saveButtonText->setPosition(450 - int(m_saveButtonText->HALF_WIDTH), 437);

    //=== Bottom bar text
    m_pauseGoToHomeLabel->setPosition(80,535);
    m_totalCoinsNbText->setPosition(450 - int(m_totalCoinsNbText->HALF_WIDTH), 535);
    m_totalCoinsNbText->setColor(GOLD_COLOR);
    m_pauseRestartLabel->setPosition(760-m_pauseRestartLabel->HALF_WIDTH,535);

    m_speedMultiplierText->setString( to_string((int)gameModel->getGameSpeed() ));
    m_currentDistanceText->setString( to_string( m_dataBase->getCurrentDistance() ) + " m" );
    m_currentCoinsNbText->setString( to_string( m_dataBase->getCurrentCoinsNumber() ) + "  X  20" );
    m_totalCoinsNbText->setString( to_string( m_dataBase->getTotalCoinsNumber() ));
    m_flattenedEnemiesText->setString( to_string( m_dataBase->getCurrentFlattenedEnemies() ));
    m_currentScoreText->setString( to_string( m_dataBase->getCurrentScore() ) );
}


/********************************************
    Menu Home Screen Drawing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::drawMenuHomeText(sf::RenderWindow *window)
{
    window->draw(*m_playButtonLabel);
    window->draw(*m_quitButtonLabel);
}


/********************************************
    Settings Screen Drawing
*********************************************
    @author Arthur  @date 14/04 - 20/05
*********************************************/
void Text::drawMenuSettingsText(sf::RenderWindow *window, int currentPage)
{
    if ( currentPage == 0)
    {
        window->draw(*m_configTitleLabel);
        window->draw(*m_configLangTitleLabel);
        window->draw(*m_configLangEngLabel);
        window->draw(*m_configLangFraLabel);
        window->draw(*m_configLangEspLabel);
        window->draw(*m_configDifficultyTitleLabel);
        window->draw(*m_configDifficultyNormalLabel);
        window->draw(*m_configDifficultyMasterLabel);
        window->draw(*m_configCustomTitleLabel);
        window->draw(*m_configDefaultBallskinLabel);
        window->draw(*m_configMorphBallskinLabel);
        window->draw(*m_configCapsuleBallskinLabel);
    }
    else
    {
        window->draw(*m_statisticsTitleLabel);
        window->draw(*m_totalDistanceLabel);
        window->draw(*m_totalFlattenedEnemiesLabel);
        window->draw(*m_totalGamesPlayedLabel);
        window->draw(*m_totalDistanceText);
        window->draw(*m_totalFlattenedEnemiesText);
        window->draw(*m_totalGamesPlayedText);
        window->draw(*m_creditsTitleLabel);
        window->draw(*m_creditsContentLabel);
        window->draw(*m_copyrightLabel);
    }
}


/********************************************
    Leaderboard Screen Drawing
*********************************************
    @author Arthur  @date 19/04 - 20/04
*********************************************/
void Text::drawLeaderboardText(sf::RenderWindow *window)
{
    window->draw(*m_leaderboardTitleLabel);
    window->draw(*m_leaderboardContentText);
    window->draw(*m_clearButtonLabel);
}


/********************************************
    Shop Screen Drawing
*********************************************
    @author Arthur  @date 16/05
*********************************************/
void Text::drawMenuShopText(sf::RenderWindow *window)
{
    window->draw(*m_totalCoinsNbText);
}


/********************************************
    Game Screen Drawing
*********************************************
    @author Arthur  @date 02/04 - 17/04
*********************************************/
void Text::drawGameText(sf::RenderWindow *window)
{
    window->draw(*m_playerLifeLabel);
    window->draw(*m_currentDistanceLabel);
    window->draw(*m_currentDistanceText);
    window->draw(*m_bonusTimeoutText);
}


/********************************************
    Pause Screen Drawing
*********************************************
    @author Arthur  @date 02/04 - 17/04
*********************************************/
void Text::drawPauseText(sf::RenderWindow *window)
{
    window->draw(*m_currentDistanceText);
    window->draw(*m_currentCoinsNbText);
    window->draw(*m_flattenedEnemiesText);
    window->draw(*m_pauseResumeLabel);
    window->draw(*m_pauseRestartLabel);
    window->draw(*m_pauseGoToHomeLabel);
}


/********************************************
    End Screen Drawing
*********************************************
    @author Arthur  @date 02/04 - 3/05
*********************************************/
void Text::drawEndText(sf::RenderWindow *window)
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
    window->draw(*m_totalCoinsNbText);
    window->draw(*m_pauseRestartLabel);
}
