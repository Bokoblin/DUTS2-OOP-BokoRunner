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
    @author Arthur  @date 2/04 - 15/04
*********************************************/
Text::~Text()
{
    delete m_font;

    delete m_playButtonText;
    delete m_quitButtonText;

    //=== Settings Text

    delete m_settingsLabel;
    delete  m_configurationLabel;
    delete m_configLanguageLabel;
    delete m_configLanguageEnLabel;
    delete m_configLanguageFrLabel;
    delete m_configLanguageEsLabel;
    delete m_configDifficultyLabel;
    delete m_configDifficultyNormalLabel;
    delete m_configDifficultyMasterLabel;

    //=== Game Text

    delete m_distanceText;
    delete m_playerLifeLabel;
    delete m_bonusTimeoutText;

    //=== Pause Text

    delete m_pauseResumeLabel;
    delete m_restartLabel;
    delete m_homeLabel;
    delete m_coinsCollectedNumberText;

    //=== End Text

    delete m_endTitleLabel;
    delete m_gameSpeedmultiplicatorLabel;
    delete m_gameSpeedmultiplicatorText;
    delete m_distanceLabel;
    delete m_coinsCollectedNumberLabel;
    delete m_enemyDestructedBonusLabel;
    delete m_enemyDestructedBonusText;
    delete m_scoreLabel;
    delete m_scoreText;
}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 02/04
*********************************************/
sf::Text *Text::getPauseResumeText() { return m_pauseResumeLabel; }
sf::Text *Text::getRestartText() { return m_restartLabel; }
sf::Text *Text::getHomeText() { return m_homeLabel; }


/********************************************
    Text Loading
*********************************************
    @author Arthur  @date 02/04
*********************************************/
void Text::loadText()
{
    m_playButtonText = new sf::Text;
    m_textVector[m_playButtonText] = "m_playButtonText";

    m_quitButtonText = new sf::Text;
    m_textVector[m_quitButtonText] = "m_quitButtonText";

    m_settingsLabel = new sf::Text;
    m_textVector[m_settingsLabel] = "m_settingsLabel";

    m_configurationLabel = new sf::Text;
    m_textVector[m_configurationLabel] = "m_configurationLabel";

    m_configLanguageLabel = new sf::Text;
    m_textVector[m_configLanguageLabel] = "m_configLanguageLabel";

    m_configLanguageEnLabel = new sf::Text;
    m_textVector[m_configLanguageEnLabel] = "m_configLanguageEnLabel";

    m_configLanguageFrLabel = new sf::Text;
    m_textVector[m_configLanguageFrLabel] = "m_configLanguageFrLabel";

    m_configLanguageEsLabel = new sf::Text;
    m_textVector[m_configLanguageEsLabel] = "m_configLanguageEsLabel";

    m_configDifficultyLabel = new sf::Text;
    m_textVector[m_configDifficultyLabel] = "m_configDifficultyLabel";

    m_configDifficultyNormalLabel = new sf::Text;
    m_textVector[m_configDifficultyNormalLabel] = "m_configDifficultyNormalLabel";

    m_configDifficultyMasterLabel = new sf::Text;
    m_textVector[m_configDifficultyMasterLabel] = "m_configDifficultyMasterLabel";

    m_distanceText = new sf::Text;
    m_textVector[m_distanceText] = "m_distanceText";

    m_playerLifeLabel = new sf::Text;
    m_textVector[m_playerLifeLabel] = "m_playerLifeLabel";

    m_bonusTimeoutText = new sf::Text;
    m_textVector[m_bonusTimeoutText] = "m_bonusTimeoutText";

    m_coinsCollectedNumberText = new sf::Text;
    m_textVector[m_coinsCollectedNumberText] = "m_CoinsCollectedNumberText";

    m_pauseResumeLabel = new sf::Text;
    m_textVector[m_pauseResumeLabel] = "m_pauseResumeLabel";

    m_restartLabel = new sf::Text;
    m_textVector[m_restartLabel] = "m_restartLabel";

    m_homeLabel = new sf::Text;
    m_textVector[m_homeLabel] = "m_homeLabel";

    m_endTitleLabel = new sf::Text;
    m_textVector[m_endTitleLabel] = "m_endTitleLabel";

    m_gameSpeedmultiplicatorLabel = new sf::Text;
    m_textVector[m_gameSpeedmultiplicatorLabel] = "m_gameSpeedmultiplicatorLabel";

    m_gameSpeedmultiplicatorText = new sf::Text;
    m_textVector[m_gameSpeedmultiplicatorText] = "m_gameSpeedmultiplicatorText";

    m_distanceLabel = new sf::Text;
    m_textVector[m_distanceLabel] = "m_distanceLabel";

    m_coinsCollectedNumberLabel = new sf::Text;
    m_textVector[m_coinsCollectedNumberLabel] = "m_CoinsCollectedNumberLabel";

    m_enemyDestructedBonusLabel = new sf::Text;
    m_textVector[m_enemyDestructedBonusLabel] = "m_enemyDestructedBonusLabel";

    m_enemyDestructedBonusText = new sf::Text;
    m_textVector[m_enemyDestructedBonusText] = "m_enemyDestructedBonusText";

    m_scoreLabel = new sf::Text;
    m_textVector[m_scoreLabel] = "m_scoreLabel";

    m_scoreText = new sf::Text;
    m_textVector[m_scoreText] = "m_scoreText";


    changeLanguage("en");

}


/********************************************
    Change Language
*********************************************
    @author Arthur  @date 13/04
*********************************************/
void Text::changeLanguage(string language)
{
    for ( map<sf::Text*, string>::iterator it = m_textVector.begin(); it !=m_textVector.end(); ++it)
    {
        it->first->setCharacterSize(24);
        it->first->setFont(*m_font);
        it->first->setColor(sf::Color::White);
        if ( language == "en")
        {
            updateString(ENGLISH_STRINGS, it->first, it->second);
        }
        else if ( language == "fr")
        {
            updateString(FRENCH_STRINGS, it->first, it->second);
        }
        else if ( language == "es")
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
	currentText->setString( result );
}


/********************************************
    Menu Home Text Syncing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::syncMenuHomeText(int width, int height)
{
    m_playButtonText->setPosition( width/2 - m_playButtonText->getGlobalBounds().width/2, height/1.42 );
    m_quitButtonText->setPosition( width/2 - m_quitButtonText->getGlobalBounds().width/2, height/1.15 );
}


/********************************************
    Menu Settings Text Syncing
*********************************************
    @author Arthur  @date 14/04
*********************************************/
void Text::syncMenuSettingsText(int width, int height)
{
    m_configurationLabel->setPosition(width/4 - m_configurationLabel->getGlobalBounds().width/2, height/10);
    m_configLanguageLabel->setPosition(40, 150);
    m_configLanguageEnLabel->setPosition(80, 202);
    m_configLanguageFrLabel->setPosition(80, 242);
    m_configLanguageEsLabel->setPosition(80, 282);
    m_configDifficultyLabel->setPosition(40, 370);
    m_configDifficultyNormalLabel->setPosition(80, 417);
    m_configDifficultyMasterLabel->setPosition(80, 457);
}

/********************************************
    Game Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 17/04
*********************************************/
void Text::syncGameMainText(GameModel *gameModel)
{
    m_playerLifeLabel->setPosition(40,545);
    m_distanceLabel->setPosition(440, 545);
    m_distanceText->setPosition(640,545);
    m_distanceText->setColor(sf::Color::White);
    m_distanceText->setString( to_string(gameModel->getDistance() ) + " m" );
    m_bonusTimeoutText->setPosition(840,545);
    if ( gameModel->getBonusTimeout() > 0)
        m_bonusTimeoutText->setString( to_string(gameModel->getBonusTimeout() ));
    else
        m_bonusTimeoutText->setString("");
}


/********************************************
    Game Pause Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 17/04
*********************************************/
void Text::syncGamePauseText(GameModel *gameModel)
{
    m_distanceText->setPosition(80, 30);
    m_coinsCollectedNumberText->setPosition(80, 70);
    m_coinsCollectedNumberText->setColor(sf::Color(255,204,0,255));
    m_enemyDestructedBonusText->setPosition(80, 110);
    m_enemyDestructedBonusText->setColor(sf::Color(0,232,209,255));
    m_pauseResumeLabel->setPosition(80, 400);
    m_restartLabel->setPosition(80, 450);
    m_homeLabel->setPosition(80, 500);

    m_distanceText->setString( to_string(gameModel->getDistance() ) + " m" );
    m_coinsCollectedNumberText->setString(to_string(gameModel->getNbCoinsCollected() ));
    m_enemyDestructedBonusText->setString( to_string( gameModel->getEnemyDestructedBonus() ));

}

/********************************************
    Game End Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::syncGameEndText(GameModel *gameModel)
{
    m_endTitleLabel->setPosition(400, 80);
    m_gameSpeedmultiplicatorLabel->setPosition(220, 170);
    m_gameSpeedmultiplicatorText->setPosition(580, 170);
    m_gameSpeedmultiplicatorText->setColor(sf::Color(86,103,97,255));
    m_distanceLabel->setPosition(220, 207);
    m_distanceLabel->setColor(sf::Color::White);
    m_distanceText->setPosition(580, 207);
    m_distanceText->setColor(sf::Color(86,103,97,255));
    m_coinsCollectedNumberLabel->setPosition(220, 245);
    m_coinsCollectedNumberText->setPosition(580, 245);
    m_coinsCollectedNumberText->setColor(sf::Color(86,103,97,255));
    m_enemyDestructedBonusLabel->setPosition(220, 290);
    m_enemyDestructedBonusLabel->setColor(sf::Color::White);
    m_enemyDestructedBonusText->setPosition(580, 290);
    m_enemyDestructedBonusText->setColor(sf::Color(86,103,97,255));
    m_scoreLabel->setPosition(220,350);
    m_scoreLabel->setStyle(sf::Text::Bold);
    m_scoreText->setPosition(580,350);
    m_scoreText->setStyle(sf::Text::Bold);
    m_homeLabel->setPosition(80,535);
    m_restartLabel->setPosition(760-m_restartLabel->getGlobalBounds().width/2,535);

    m_gameSpeedmultiplicatorText->setString(  to_string( gameModel->getGameSpeed() + 2*gameModel->getDifficulty() ));
    m_distanceText->setString(  to_string( gameModel->getDistance() ) + " m" );
    m_coinsCollectedNumberText->setString( to_string( gameModel->getNbCoinsCollected() ) + "  X  20" );
    m_enemyDestructedBonusText->setString( to_string( gameModel->getEnemyDestructedBonus() ));
    m_scoreText->setString( to_string( gameModel->getScore() ) );
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
    @author Arthur  @date 14/04
*********************************************/
void Text::drawMenuSettingsText(sf::RenderWindow *window)
{
    window->draw(*m_configurationLabel);
    window->draw(*m_configLanguageLabel);
    window->draw(*m_configLanguageEnLabel);
    window->draw(*m_configLanguageFrLabel);
    window->draw(*m_configLanguageEsLabel);
    window->draw(*m_configDifficultyLabel);
    window->draw(*m_configDifficultyNormalLabel);
    window->draw(*m_configDifficultyMasterLabel);
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
    window->draw(*m_coinsCollectedNumberText);
    window->draw(*m_enemyDestructedBonusText);
    window->draw(*m_pauseResumeLabel);
    window->draw(*m_restartLabel);
    window->draw(*m_homeLabel);
}


/********************************************
    End Screen Drawing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::drawEndText(sf::RenderWindow *window)
{
    window->draw(*m_endTitleLabel);
    window->draw(*m_gameSpeedmultiplicatorLabel);
    window->draw(*m_gameSpeedmultiplicatorText);
    window->draw(*m_distanceLabel);
    window->draw(*m_distanceText);
    window->draw(*m_coinsCollectedNumberLabel);
    window->draw(*m_coinsCollectedNumberText);
    window->draw(*m_enemyDestructedBonusLabel);
    window->draw(*m_enemyDestructedBonusText);
    window->draw(*m_scoreLabel);
    window->draw(*m_scoreText);
    window->draw(*m_homeLabel);
    window->draw(*m_restartLabel);
}
