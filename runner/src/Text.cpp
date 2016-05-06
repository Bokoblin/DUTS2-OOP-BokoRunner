#include "../header/Text.h"

using namespace std;

/********************************************
    Default Constructor
*********************************************
    @author Arthur  @date 02/04 - 6/05
*********************************************/
Text::Text(DataModel *dataModel) : m_dataModel{dataModel}
{
    m_font = new sf::Font();
    m_font->loadFromFile(ROBOTO_FONT);

    loadText();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 2/04 - 6/05
*********************************************/
Text::~Text()
{
    for ( map<sf::Text*, string>::iterator it = m_textMap.begin();
        it !=m_textMap.end(); ++it) delete it->first;

    delete m_font;
}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 02/04
*********************************************/
sf::Text *Text::getResumeText() const { return m_pauseResumeLabel; }
sf::Text *Text::getRestartText() const { return m_pauseRestartLabel; }
sf::Text *Text::getHomeText() const { return m_pauseGoToHomeLabel; }

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

    m_configDifficultyLabel = new sf::Text;
    m_textMap[m_configDifficultyLabel] = "configDifficultyLabel";

    m_configDifficultyNormalLabel = new sf::Text;
    m_textMap[m_configDifficultyNormalLabel] = "configDifficultyNormalLabel";

    m_configDifficultyMasterLabel = new sf::Text;
    m_textMap[m_configDifficultyMasterLabel] = "configDifficultyMasterLabel";

    m_statisticsTitleLabel = new sf::Text;
    m_textMap[m_statisticsTitleLabel] = "statisticsTitleLabel";

    m_totalDistanceLabel = new sf::Text;
    m_textMap[m_totalDistanceLabel] = "totalDistanceLabel";

    m_totalCoinsCollectedText = new sf::Text;
    m_textMap[m_totalCoinsCollectedText] = "totalCoinsText";

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

    m_currentCoinsCollectedText = new sf::Text;
    m_textMap[m_currentCoinsCollectedText] = "CoinsCollectedNumberText";

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
        it->first->setCharacterSize(24);
        it->first->setFont(*m_font);
        it->first->setColor(sf::Color::White);

        if ( m_dataModel->getLanguage() == "en")
        {
            updateString(ENGLISH_STRINGS, it->first, it->second);
        }
        else if ( m_dataModel->getLanguage() == "fr")
        {
            updateString(FRENCH_STRINGS, it->first, it->second);
        }
        else if ( m_dataModel->getLanguage() == "es")
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
void Text::syncMenuHomeText(int width, int height)
{
    m_playButtonLabel->setPosition( width/2 -
        int(m_playButtonLabel->getGlobalBounds().width/2), height/1.42 );
    m_quitButtonLabel->setPosition( width/2 -
        int(m_quitButtonLabel->getGlobalBounds().width/2), height/1.15 );
}


/********************************************
    Menu Settings Text Syncing
*********************************************
    @author Arthur  @date 14/04 - 2/05
*********************************************/
void Text::syncMenuSettingsText(MenuModel *menuModel, int width, int height)
{
    m_configTitleLabel->setPosition(width/4 -
        int(m_configTitleLabel->getGlobalBounds().width/2), height/10);
    m_configLangTitleLabel->setPosition(40, 150);
    m_configLangEngLabel->setPosition(80, 202);
    m_configLangFraLabel->setPosition(80, 242);
    m_configLangEspLabel->setPosition(80, 282);
    m_configDifficultyLabel->setPosition(40, 370);
    m_configDifficultyNormalLabel->setPosition(80, 417);
    m_configDifficultyMasterLabel->setPosition(80, 457);
    m_statisticsTitleLabel->setPosition( width - (width/4 +
        int(m_configTitleLabel->getGlobalBounds().width/2)), height/10);
    m_totalDistanceLabel->setPosition(450, 170);
    m_totalFlattenedEnemiesLabel->setPosition(450, 220);
    m_totalGamesPlayedLabel->setPosition(450, 270);
    m_totalDistanceText->setPosition(750, 170);
    m_totalFlattenedEnemiesText->setPosition(750, 220);
    m_totalGamesPlayedText->setPosition(750, 270);

    m_totalDistanceText->setString( to_string(
            m_dataModel->getTotalDistanceTravelled() ) + " m" );
    m_totalFlattenedEnemiesText->setString( to_string(
            m_dataModel->getTotalEnemiesDestructed() ) );
    m_totalGamesPlayedText->setString( to_string(
            m_dataModel->getTotalGamesPlayed() ) );
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
            int(m_leaderboardContentText->getGlobalBounds().width/2), 250);
    }
    else if ( scores == "empty")
    {
        m_textMap[m_leaderboardContentText] = "leaderboardText";
        updateWholeText();
        m_leaderboardContentText->setPosition(w/2 -
                int(m_leaderboardContentText->getGlobalBounds().width/2), 250);
    }
    else //valid and not empty
    {
        m_textMap[m_leaderboardContentText] = "leaderboardText";
        m_leaderboardContentText->setString(scores);
        m_leaderboardContentText->setCharacterSize(30);
        m_leaderboardContentText->setPosition(w/2 -
                int(m_leaderboardContentText->getGlobalBounds().width/2), 100);
    }

    m_leaderboardTitleLabel->setPosition(w/2 -
            int(m_leaderboardTitleLabel->getGlobalBounds().width/2), h/10);

    m_clearButtonLabel->setCharacterSize(20);
    m_clearButtonLabel->setPosition(w/2 -
            int(m_clearButtonLabel->getGlobalBounds().width/2), 507);
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
            m_dataModel->getCurrentDistance() ) + " m" );
    m_bonusTimeoutText->setPosition(840,545);
    if ( gameModel->getBonusTimeout() > 0)
        m_bonusTimeoutText->setString( to_string(gameModel->getBonusTimeout() ) );
    else
        m_bonusTimeoutText->setString("");
}


/********************************************
    Game Pause Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 6/05
*********************************************/
void Text::syncPauseText(GameModel *gameModel)
{
    m_currentDistanceText->setPosition(80, 30);
    m_currentCoinsCollectedText->setPosition(80, 70);
    m_currentCoinsCollectedText->setColor(sf::Color(255,204,0,255));
    m_flattenedEnemiesText->setPosition(80, 110);
    m_flattenedEnemiesText->setColor(sf::Color(0,232,209,255));
    m_pauseResumeLabel->setPosition(80, 400);
    m_pauseRestartLabel->setPosition(80, 450);
    m_pauseGoToHomeLabel->setPosition(80, 500);

    m_currentCoinsCollectedText->setString(to_string(
            m_dataModel->getCurrentCoinsCollected() ) );
    m_flattenedEnemiesText->setString(to_string(
            m_dataModel->getCurrentFlattenedEnemies() ) );
}

/********************************************
    Game End Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 6/05
*********************************************/
void Text::syncEndText(GameModel *gameModel)
{
    //score calculating text
    m_endTitleLabel->setPosition(400, 80);
    m_speedMultiplierLabel->setPosition(220, 170);
    m_speedMultiplierText->setPosition(580, 170);
    m_speedMultiplierText->setColor(sf::Color(86,103,97,255));
    m_currentDistanceLabel->setPosition(220, 207);
    m_currentDistanceLabel->setColor(sf::Color::White);
    m_currentDistanceText->setPosition(580, 207);
    m_currentDistanceText->setColor(sf::Color(86,103,97,255));
    m_coinsCollectedLabel->setPosition(220, 245);
    m_currentCoinsCollectedText->setPosition(580, 245);
    m_currentCoinsCollectedText->setColor(sf::Color(86,103,97,255));
    m_flattenedEnemiesLabel->setPosition(220, 290);
    m_flattenedEnemiesLabel->setColor(sf::Color::White);
    m_flattenedEnemiesText->setPosition(580, 290);
    m_flattenedEnemiesText->setColor(sf::Color(86,103,97,255));
    m_currentScoreLabel->setPosition(220,350);
    m_currentScoreLabel->setStyle(sf::Text::Bold);
    m_currentScoreText->setPosition(580,350);
    m_currentScoreText->setStyle(sf::Text::Bold);
    m_saveButtonText->setCharacterSize(20);
    if ( gameModel->getSaveStatus() == false)
            m_saveButtonText->setPosition(-100, -100);
    else
        m_saveButtonText->setPosition(450 - int(m_saveButtonText->getGlobalBounds().width/2), 437);

    //bottom bar text
    m_pauseGoToHomeLabel->setPosition(80,535);
    m_totalCoinsCollectedText->setPosition(450 - int(m_totalCoinsCollectedText->getGlobalBounds().width/2), 535);
    m_totalCoinsCollectedText->setColor(sf::Color(255,204,0,255));
    m_pauseRestartLabel->setPosition(760-m_pauseRestartLabel->getGlobalBounds().width/2,535);

    m_speedMultiplierText->setString( to_string((int)gameModel->getGameSpeed() ));
    m_currentDistanceText->setString( to_string( m_dataModel->getCurrentDistance() ) + " m" );
    m_currentCoinsCollectedText->setString( to_string( m_dataModel->getCurrentCoinsCollected() ) + "  X  20" );
    m_totalCoinsCollectedText->setString( to_string( m_dataModel->getTotalCoinsCollected() ));
    m_flattenedEnemiesText->setString( to_string( m_dataModel->getCurrentFlattenedEnemies() ));
    m_currentScoreText->setString( to_string( m_dataModel->getCurrentScore() ) );
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
    Menu Settings Screen Drawing
*********************************************
    @author Arthur  @date 14/04 - 2/05
*********************************************/
void Text::drawMenuSettingsText(sf::RenderWindow *window)
{
    window->draw(*m_configTitleLabel);
    window->draw(*m_configLangTitleLabel);
    window->draw(*m_configLangEngLabel);
    window->draw(*m_configLangFraLabel);
    window->draw(*m_configLangEspLabel);
    window->draw(*m_configDifficultyLabel);
    window->draw(*m_configDifficultyNormalLabel);
    window->draw(*m_configDifficultyMasterLabel);
    window->draw(*m_statisticsTitleLabel);
    window->draw(*m_totalDistanceLabel);
    window->draw(*m_totalFlattenedEnemiesLabel);
    window->draw(*m_totalGamesPlayedLabel);
    window->draw(*m_totalDistanceText);
    window->draw(*m_totalFlattenedEnemiesText);
    window->draw(*m_totalGamesPlayedText);
}


/********************************************
    Menu Leaderboard Screen Drawing
*********************************************
    @author Arthur  @date 19/04 - 20/04
*********************************************/
void Text::drawMenuLeaderboardText(sf::RenderWindow *window)
{
    window->draw(*m_leaderboardTitleLabel);
    window->draw(*m_leaderboardContentText);
    window->draw(*m_clearButtonLabel);
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
    window->draw(*m_currentCoinsCollectedText);
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
    window->draw(*m_currentCoinsCollectedText);
    window->draw(*m_flattenedEnemiesLabel);
    window->draw(*m_flattenedEnemiesText);
    window->draw(*m_currentScoreLabel);
    window->draw(*m_currentScoreText);
    window->draw(*m_saveButtonText);
    window->draw(*m_pauseGoToHomeLabel);
    window->draw(*m_totalCoinsCollectedText);
    window->draw(*m_pauseRestartLabel);
}
