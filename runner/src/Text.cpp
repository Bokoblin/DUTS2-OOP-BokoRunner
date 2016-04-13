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
    @author Arthur  @date 2/04
*********************************************/
Text::~Text()
{
    if(m_font!= NULL)
        delete m_font;
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

    m_distanceText = new sf::Text;
    m_textVector[m_distanceText] = "m_distanceText";

    m_playerLifeLabel = new sf::Text;
    m_textVector[m_playerLifeLabel] = "m_playerLifeLabel";

    m_CoinsCollectedNumberText = new sf::Text;
    m_textVector[m_CoinsCollectedNumberText] = "m_CoinsCollectedNumberText";

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
        it->first->setFont(*m_font);
        it->first->setColor(sf::Color::White);
        if ( language == "en")
        {
            it->first->setCharacterSize(24);
            updateString(ENGLISH_STRINGS, it->first, it->second);
        }
        else if ( language == "fr")
        {
            it->first->setCharacterSize(22);
            updateString(FRENCH_STRINGS, it->first, it->second);
        }
        else if ( language == "es")
        {
            it->first->setCharacterSize(22);
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
    Menu Text Syncing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::syncMenuText(int width, int height)
{
    m_playButtonText->setPosition( width/2-30, height/1.42 );
    m_quitButtonText->setPosition( width/2-30, height/1.15 );
}


/********************************************
    Game Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::syncGameText(GameModel *gameModel)
{
    m_playerLifeLabel->setPosition(40,545);
    m_distanceLabel->setPosition(530, 545);
    m_distanceText->setPosition(750,545);
    m_distanceText->setString( to_string(gameModel->getDistance() ) + " m" );
}


/********************************************
    Pause Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::syncPauseText(GameModel *gameModel)
{
    m_distanceText->setPosition(80, 30);
    m_CoinsCollectedNumberText->setPosition(80, 70);
    m_CoinsCollectedNumberText->setColor(sf::Color(255,204,0,255));
    m_pauseResumeLabel->setPosition(80, 400);
    m_restartLabel->setPosition(80, 450);
    m_homeLabel->setPosition(80, 500);

    m_distanceText->setString( to_string(gameModel->getDistance() ) + " m" );
    m_CoinsCollectedNumberText->setString(to_string(gameModel->getNbCoinsCollected() ));

}

/********************************************
    End Screen Syncing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::syncEndText(GameModel *gameModel)
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
    m_CoinsCollectedNumberText->setPosition(580, 245);
    m_CoinsCollectedNumberText->setColor(sf::Color(86,103,97,255));
    m_enemyDestructedBonusLabel->setPosition(220, 290);
    m_enemyDestructedBonusLabel->setColor(sf::Color::White);
    m_enemyDestructedBonusText->setPosition(580, 290);
    m_enemyDestructedBonusText->setColor(sf::Color(86,103,97,255));
    m_scoreLabel->setPosition(220,350);
    m_scoreLabel->setStyle(sf::Text::Bold);
    m_scoreText->setPosition(580,350);
    m_scoreText->setStyle(sf::Text::Bold);
    m_homeLabel->setPosition(80,535);
    m_restartLabel->setPosition(750,535);

    m_gameSpeedmultiplicatorText->setString(  to_string( gameModel->getGameSpeed() ));
    m_distanceText->setString(  to_string( gameModel->getDistance() ) + " m" );
    m_CoinsCollectedNumberText->setString( to_string( gameModel->getNbCoinsCollected() ) + "  X  20" );
    m_enemyDestructedBonusText->setString( to_string( gameModel->getEnemyDestructedBonus() ));
    m_scoreText->setString( to_string( gameModel->getScore() ) );
}


/********************************************
    Menu Screen Drawing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::drawMenuText(sf::RenderWindow *window)
{
    window->draw(*m_playButtonText);
    window->draw(*m_quitButtonText);
}


/********************************************
    Game Screen Drawing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::drawGameText(sf::RenderWindow *window)
{
    window->draw(*m_playerLifeLabel);
    window->draw(*m_distanceLabel);
    window->draw(*m_distanceText);
}


/********************************************
    Pause Screen Drawing
*********************************************
    @author Arthur  @date 02/04 - 13/04
*********************************************/
void Text::drawPauseText(sf::RenderWindow *window)
{
    window->draw(*m_distanceText);
    window->draw(*m_CoinsCollectedNumberText);
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
    window->draw(*m_CoinsCollectedNumberText);
    window->draw(*m_enemyDestructedBonusLabel);
    window->draw(*m_enemyDestructedBonusText);
    window->draw(*m_scoreLabel);
    window->draw(*m_scoreText);
    window->draw(*m_homeLabel);
    window->draw(*m_restartLabel);
}
