#include "../header/Text.h"

using namespace std;

/********************************************
    Default Constructor
*********************************************
    @author Arthur  @date 02/04
*********************************************/
Text::Text()
{
    m_font = new sf::Font();
    m_font->loadFromFile(ROBOTO_FONT);

    loadText();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 2/04 - 3/05
*********************************************/
Text::~Text()
{
    delete m_font;

    delete m_playButtonText;
    delete m_quitButtonText;

    //=== Settings Text

    //config
    delete m_settingsLabel;
    delete m_configTitleLabel;
    delete m_configLanguageLabel;
    delete m_configLanguageEnLabel;
    delete m_configLanguageFrLabel;
    delete m_configLanguageEsLabel;
    delete m_configDifficultyLabel;
    delete m_configDifficultyNormalLabel;
    delete m_configDifficultyMasterLabel;
    delete m_leaderboardTitleLabel;
    delete m_leaderboardText;
    delete m_clearButtonText;
    //stats
    delete m_statTitlesLabel;
    delete m_totalDistanceLabel;
    delete m_totalEnemiesDestructedLabel;
    delete m_totalGamesPlayedLabel;
    delete m_totalDistanceText;
    delete m_totalEnemiesDestructedText;
    delete m_totalGamesPlayedText;

    //=== Game Text

    delete m_distanceText;
    delete m_playerLifeLabel;
    delete m_bonusTimeoutText;
    delete m_saveButtonText;

    //=== Pause Text

    delete m_pauseResumeLabel;
    delete m_restartLabel;
    delete m_homeLabel;
    delete m_coinsCollectedText;

    //=== End Text

    delete m_endTitleLabel;
    delete m_speedmultiplicatorLabel;
    delete m_speedmultiplicatorText;
    delete m_distanceLabel;
    delete m_coinsCollectedLabel;
    delete m_enemyDestructedBonusLabel;
    delete m_enemyDestructedBonusText;
    delete m_scoreLabel;
    delete m_scoreText;
    delete m_saveButtonText;
}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 02/04
*********************************************/
sf::Text *Text::getResumeText() const { return m_pauseResumeLabel; }
sf::Text *Text::getRestartText() const { return m_restartLabel; }
sf::Text *Text::getHomeText() const { return m_homeLabel; }
string Text::getLanguage() const {return m_currentLanguage;}


/********************************************
    Setters
*********************************************
    @author Arthur  @date 20/04
*********************************************/
void Text::setLanguage(string lang) { m_currentLanguage = lang;}


/********************************************
    Text Loading
*********************************************
    @author Arthur  @date 02/04 - 2/05
*********************************************/
void Text::loadText()
{
    m_playButtonText = new sf::Text;
    m_textVector[m_playButtonText] = "playButtonText";

    m_quitButtonText = new sf::Text;
    m_textVector[m_quitButtonText] = "quitButtonText";

    m_settingsLabel = new sf::Text;
    m_textVector[m_settingsLabel] = "settingsLabel";

    m_configTitleLabel = new sf::Text;
    m_textVector[m_configTitleLabel] = "configurationLabel";

    m_configLanguageLabel = new sf::Text;
    m_textVector[m_configLanguageLabel] = "configLanguageLabel";

    m_configLanguageEnLabel = new sf::Text;
    m_textVector[m_configLanguageEnLabel] = "configLanguageEnLabel";

    m_configLanguageFrLabel = new sf::Text;
    m_textVector[m_configLanguageFrLabel] = "configLanguageFrLabel";

    m_configLanguageEsLabel = new sf::Text;
    m_textVector[m_configLanguageEsLabel] = "configLanguageEsLabel";

    m_configDifficultyLabel = new sf::Text;
    m_textVector[m_configDifficultyLabel] = "configDifficultyLabel";

    m_configDifficultyNormalLabel = new sf::Text;
    m_textVector[m_configDifficultyNormalLabel] = "configDifficultyNormalLabel";

    m_configDifficultyMasterLabel = new sf::Text;
    m_textVector[m_configDifficultyMasterLabel] = "configDifficultyMasterLabel";

    m_statTitlesLabel = new sf::Text;
    m_textVector[m_statTitlesLabel] = "statsLabel";

    m_totalDistanceLabel = new sf::Text;
    m_textVector[m_totalDistanceLabel] = "totalDistanceLabel";

    m_totalCoinsText = new sf::Text;
    m_textVector[m_totalCoinsText] = "totalCoinsText";

    m_totalEnemiesDestructedLabel = new sf::Text;
    m_textVector[m_totalEnemiesDestructedLabel] = "totalEnemiesDestructedLabel";

    m_totalGamesPlayedLabel = new sf::Text;
    m_textVector[m_totalGamesPlayedLabel] = "totalGamesPlayedLabel";

    m_totalDistanceText = new sf::Text;
    m_textVector[m_totalDistanceText] = "totalDistanceText";

    m_totalEnemiesDestructedText = new sf::Text;
    m_textVector[m_totalEnemiesDestructedText] = "totalEnemiesDestructedText";

    m_totalGamesPlayedText = new sf::Text;
    m_textVector[m_totalGamesPlayedText] = "totalGamesPlayedText";

    m_leaderboardTitleLabel = new sf::Text;
    m_textVector[m_leaderboardTitleLabel] = "leaderboardTitleLabel";

    m_leaderboardText = new sf::Text;
    m_textVector[m_leaderboardText] = "leaderboardText";

    m_clearButtonText = new sf::Text;
    m_textVector[m_clearButtonText] = "clearButtonText";

    m_distanceText = new sf::Text;
    m_textVector[m_distanceText] = "distanceText";

    m_playerLifeLabel = new sf::Text;
    m_textVector[m_playerLifeLabel] = "playerLifeLabel";

    m_bonusTimeoutText = new sf::Text;
    m_textVector[m_bonusTimeoutText] = "bonusTimeoutText";

    m_coinsCollectedText = new sf::Text;
    m_textVector[m_coinsCollectedText] = "CoinsCollectedNumberText";

    m_pauseResumeLabel = new sf::Text;
    m_textVector[m_pauseResumeLabel] = "pauseResumeLabel";

    m_restartLabel = new sf::Text;
    m_textVector[m_restartLabel] = "restartLabel";

    m_homeLabel = new sf::Text;
    m_textVector[m_homeLabel] = "homeLabel";

    m_endTitleLabel = new sf::Text;
    m_textVector[m_endTitleLabel] = "endTitleLabel";

    m_saveButtonText = new sf::Text;
    m_textVector[m_saveButtonText] = "saveButtonText";

    m_speedmultiplicatorLabel = new sf::Text;
    m_textVector[m_speedmultiplicatorLabel] = "speedmultiplicatorLabel";

    m_speedmultiplicatorText = new sf::Text;
    m_textVector[m_speedmultiplicatorText] = "speedmultiplicatorText";

    m_distanceLabel = new sf::Text;
    m_textVector[m_distanceLabel] = "distanceLabel";

    m_coinsCollectedLabel = new sf::Text;
    m_textVector[m_coinsCollectedLabel] = "CoinsCollectedNumberLabel";

    m_enemyDestructedBonusLabel = new sf::Text;
    m_textVector[m_enemyDestructedBonusLabel] = "enemyDestructedBonusLabel";

    m_enemyDestructedBonusText = new sf::Text;
    m_textVector[m_enemyDestructedBonusText] = "enemyDestructedBonusText";

    m_scoreLabel = new sf::Text;
    m_textVector[m_scoreLabel] = "scoreLabel";

    m_scoreText = new sf::Text;
    m_textVector[m_scoreText] = "scoreText";

    m_currentLanguage = "en";
    updateWholeText();

}


/********************************************
    Change Language
*********************************************
    @author Arthur  @date 13/04
*********************************************/
void Text::updateWholeText()
{
    for ( map<sf::Text*, string>::iterator it = m_textVector.begin();
          it !=m_textVector.end(); ++it)
    {
        it->first->setCharacterSize(24);
        it->first->setFont(*m_font);
        it->first->setColor(sf::Color::White);

        if ( m_currentLanguage == "en")
        {
            updateString(ENGLISH_STRINGS, it->first, it->second);
        }
        else if ( m_currentLanguage == "fr")
        {
            updateString(FRENCH_STRINGS, it->first, it->second);
        }
        else if ( m_currentLanguage == "es")
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
void Text::updateString(string file, sf::Text *currentText, string currentName)
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
		found=line.find("name=\""+ currentName + "\"");
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
    currentText->setString(result);
}


/********************************************
    Menu Home Text Syncing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::syncMenuHomeText(int width, int height)
{
    m_playButtonText->setPosition( width/2 -
        int(m_playButtonText->getGlobalBounds().width/2), height/1.42 );
    m_quitButtonText->setPosition( width/2 -
        int(m_quitButtonText->getGlobalBounds().width/2), height/1.15 );
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
    m_configLanguageLabel->setPosition(40, 150);
    m_configLanguageEnLabel->setPosition(80, 202);
    m_configLanguageFrLabel->setPosition(80, 242);
    m_configLanguageEsLabel->setPosition(80, 282);
    m_configDifficultyLabel->setPosition(40, 370);
    m_configDifficultyNormalLabel->setPosition(80, 417);
    m_configDifficultyMasterLabel->setPosition(80, 457);
    m_statTitlesLabel->setPosition( width - (width/4 +
        int(m_configTitleLabel->getGlobalBounds().width/2)), height/10);
    m_totalDistanceLabel->setPosition(450, 170);
    m_totalEnemiesDestructedLabel->setPosition(450, 220);
    m_totalGamesPlayedLabel->setPosition(450, 270);
    m_totalDistanceText->setPosition(750, 170);
    m_totalEnemiesDestructedText->setPosition(750, 220);
    m_totalGamesPlayedText->setPosition(750, 270);

    m_totalDistanceText->setString( to_string(menuModel->getDataModel()->getTotalDistanceTravelled() ) + " m" );
    m_totalEnemiesDestructedText->setString( to_string(menuModel->getDataModel()->getTotalEnemiesDestructed()));
    m_totalGamesPlayedText->setString( to_string(menuModel->getDataModel()->getTotalGamesPlayed() ) );
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
        m_textVector[m_leaderboardText] = "leaderboardErrorText";
        updateWholeText();
        m_leaderboardText->setPosition(w/2 -
            int(m_leaderboardText->getGlobalBounds().width/2), 250);
    }
    else if ( scores == "empty")
    {
        m_textVector[m_leaderboardText] = "leaderboardText";
        updateWholeText();
        m_leaderboardText->setPosition(w/2 -
            int(m_leaderboardText->getGlobalBounds().width/2), 250);
    }
    else //valid and not empty
    {
        m_textVector[m_leaderboardText] = "leaderboardText";
        m_leaderboardText->setString(scores);
        m_leaderboardText->setCharacterSize(30);
        m_leaderboardText->setPosition(w/2 -
            int(m_leaderboardText->getGlobalBounds().width/2), 100);
    }

    m_leaderboardTitleLabel->setPosition(w/2 -
        int(m_leaderboardTitleLabel->getGlobalBounds().width/2), h/10);

    m_clearButtonText->setCharacterSize(20);
    m_clearButtonText->setPosition(w/2 -
        int(m_clearButtonText->getGlobalBounds().width/2), 507);
}

/********************************************
    Game Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 17/04
*********************************************/
void Text::syncGameText(GameModel *gameModel)
{
    m_playerLifeLabel->setPosition(40,545);
    m_distanceLabel->setPosition(440, 545);
    m_distanceText->setPosition(640,545);
    m_distanceText->setColor(sf::Color::White);
    m_distanceText->setString( to_string(gameModel->getDataModel()->getCurrentDistance() ) + " m" );
    m_bonusTimeoutText->setPosition(840,545);
    if ( gameModel->getBonusTimeout() > 0)
        m_bonusTimeoutText->setString( to_string(gameModel->getBonusTimeout()));
    else
        m_bonusTimeoutText->setString("");
}


/********************************************
    Game Pause Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 17/04
*********************************************/
void Text::syncPauseText(GameModel *gameModel)
{
    m_distanceText->setPosition(80, 30);
    m_coinsCollectedText->setPosition(80, 70);
    m_coinsCollectedText->setColor(sf::Color(255,204,0,255));
    m_enemyDestructedBonusText->setPosition(80, 110);
    m_enemyDestructedBonusText->setColor(sf::Color(0,232,209,255));
    m_pauseResumeLabel->setPosition(80, 400);
    m_restartLabel->setPosition(80, 450);
    m_homeLabel->setPosition(80, 500);

    m_distanceText->setString( to_string(gameModel->getDataModel()->getCurrentDistance() ) + " m" );
    m_coinsCollectedText->setString(to_string(gameModel->getDataModel()->getCurrentCoinsCollected() ));
    m_enemyDestructedBonusText->setString(to_string(gameModel->getDataModel()->getCurrentEnemyDestructed() ));

}

/********************************************
    Game End Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 3/05
*********************************************/
void Text::syncEndText(GameModel *gameModel)
{
    //score calculating text
    m_endTitleLabel->setPosition(400, 80);
    m_speedmultiplicatorLabel->setPosition(220, 170);
    m_speedmultiplicatorText->setPosition(580, 170);
    m_speedmultiplicatorText->setColor(sf::Color(86,103,97,255));
    m_distanceLabel->setPosition(220, 207);
    m_distanceLabel->setColor(sf::Color::White);
    m_distanceText->setPosition(580, 207);
    m_distanceText->setColor(sf::Color(86,103,97,255));
    m_coinsCollectedLabel->setPosition(220, 245);
    m_coinsCollectedText->setPosition(580, 245);
    m_coinsCollectedText->setColor(sf::Color(86,103,97,255));
    m_enemyDestructedBonusLabel->setPosition(220, 290);
    m_enemyDestructedBonusLabel->setColor(sf::Color::White);
    m_enemyDestructedBonusText->setPosition(580, 290);
    m_enemyDestructedBonusText->setColor(sf::Color(86,103,97,255));
    m_scoreLabel->setPosition(220,350);
    m_scoreLabel->setStyle(sf::Text::Bold);
    m_scoreText->setPosition(580,350);
    m_scoreText->setStyle(sf::Text::Bold);
    m_saveButtonText->setCharacterSize(20);
    if ( gameModel->getSaveStatus() == false)
            m_saveButtonText->setPosition(-100, -100);
    else
        m_saveButtonText->setPosition(450 - int(m_saveButtonText->getGlobalBounds().width/2), 437);

    //bottom bar text
    m_homeLabel->setPosition(80,535);
    m_totalCoinsText->setPosition(450 - int(m_totalCoinsText->getGlobalBounds().width/2), 535);
    m_totalCoinsText->setColor(sf::Color(255,204,0,255));
    m_restartLabel->setPosition(760-m_restartLabel->getGlobalBounds().width/2,535);

    m_speedmultiplicatorText->setString(to_string((int)gameModel->getGameSpeed() + 2*gameModel->getDifficulty() ));
    m_distanceText->setString(  to_string( gameModel->getDataModel()->getCurrentDistance() ) + " m" );
    m_coinsCollectedText->setString( to_string( gameModel->getDataModel()->getCurrentCoinsCollected() ) + "  X  20" );
    m_totalCoinsText->setString( to_string( gameModel->getDataModel()->getTotalCoinsCollected() ));
    m_enemyDestructedBonusText->setString( to_string( gameModel->getDataModel()->getCurrentEnemyDestructed() ));
    m_scoreText->setString( to_string( gameModel->getDataModel()->getCurrentScore() ) );
}


/********************************************
    Menu Home Screen Drawing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::drawMenuHomeText(sf::RenderWindow *window)
{
    window->draw(*m_playButtonText);
    window->draw(*m_quitButtonText);
}


/********************************************
    Menu Settings Screen Drawing
*********************************************
    @author Arthur  @date 14/04 - 2/05
*********************************************/
void Text::drawMenuSettingsText(sf::RenderWindow *window)
{
    window->draw(*m_configTitleLabel);
    window->draw(*m_configLanguageLabel);
    window->draw(*m_configLanguageEnLabel);
    window->draw(*m_configLanguageFrLabel);
    window->draw(*m_configLanguageEsLabel);
    window->draw(*m_configDifficultyLabel);
    window->draw(*m_configDifficultyNormalLabel);
    window->draw(*m_configDifficultyMasterLabel);
    window->draw(*m_statTitlesLabel);
    window->draw(*m_totalDistanceLabel);
    window->draw(*m_totalEnemiesDestructedLabel);
    window->draw(*m_totalGamesPlayedLabel);
    window->draw(*m_totalDistanceText);
    window->draw(*m_totalEnemiesDestructedText);
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
    window->draw(*m_leaderboardText);
    window->draw(*m_clearButtonText);
}

/********************************************
    Game Screen Drawing
*********************************************
    @author Arthur  @date 02/04 - 17/04
*********************************************/
void Text::drawGameText(sf::RenderWindow *window)
{
    window->draw(*m_playerLifeLabel);
    window->draw(*m_distanceLabel);
    window->draw(*m_distanceText);
    window->draw(*m_bonusTimeoutText);
}


/********************************************
    Pause Screen Drawing
*********************************************
    @author Arthur  @date 02/04 - 17/04
*********************************************/
void Text::drawPauseText(sf::RenderWindow *window)
{
    window->draw(*m_distanceText);
    window->draw(*m_coinsCollectedText);
    window->draw(*m_enemyDestructedBonusText);
    window->draw(*m_pauseResumeLabel);
    window->draw(*m_restartLabel);
    window->draw(*m_homeLabel);
}


/********************************************
    End Screen Drawing
*********************************************
    @author Arthur  @date 02/04 - 3/05
*********************************************/
void Text::drawEndText(sf::RenderWindow *window)
{
    window->draw(*m_endTitleLabel);
    window->draw(*m_speedmultiplicatorLabel);
    window->draw(*m_speedmultiplicatorText);
    window->draw(*m_distanceLabel);
    window->draw(*m_distanceText);
    window->draw(*m_coinsCollectedLabel);
    window->draw(*m_coinsCollectedText);
    window->draw(*m_enemyDestructedBonusLabel);
    window->draw(*m_enemyDestructedBonusText);
    window->draw(*m_scoreLabel);
    window->draw(*m_scoreText);
    window->draw(*m_saveButtonText);
    window->draw(*m_homeLabel);
    window->draw(*m_totalCoinsText);
    window->draw(*m_restartLabel);
}
