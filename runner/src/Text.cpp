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
sf::Text Text::getPauseResumeText() { return m_pauseResumeLabel; }
sf::Text Text::getRestartText() { return m_restartLabel; }
sf::Text Text::getHomeText() { return m_homeLabel; }


/********************************************
    Text Loading
*********************************************
    @author Arthur  @date 02/04
*********************************************/
void Text::loadText()
{
    //Menu Text Loading

    m_playButtonText.setFont(*m_font);
    m_playButtonText.setCharacterSize(24);
    m_playButtonText.setColor(sf::Color::White);
    m_playButtonText.setString( "PLAY" );

    m_quitButtonText.setFont(*m_font);
    m_quitButtonText.setCharacterSize(24);
    m_quitButtonText.setColor(sf::Color::White);
    m_quitButtonText.setString( "QUIT" );

    //Game Texte Loading

    m_distanceText.setFont(*m_font);
    m_distanceText.setCharacterSize(24);
    m_distanceText.setColor(sf::Color::White);
    m_distanceText.setString( "" );

    m_playerLifeLabel.setFont(*m_font);
    m_playerLifeLabel.setCharacterSize(24);
    m_playerLifeLabel.setColor(sf::Color::White);
    m_playerLifeLabel.setString( "Life " );

    //Pause Text Loading

    m_CoinsCollectedNumberText.setFont(*m_font);
    m_CoinsCollectedNumberText.setCharacterSize(24);
    m_CoinsCollectedNumberText.setColor(sf::Color(255,204,0,255));
    m_CoinsCollectedNumberText.setString( "" );

    m_pauseResumeLabel.setFont(*m_font);
    m_pauseResumeLabel.setCharacterSize(24);
    m_pauseResumeLabel.setColor(sf::Color::White);
    m_pauseResumeLabel.setString( "Resume" );

    m_restartLabel.setFont(*m_font);
    m_restartLabel.setCharacterSize(24);
    m_restartLabel.setColor(sf::Color::White);
    m_restartLabel.setString( "Restart" );

    m_homeLabel.setFont(*m_font);
    m_homeLabel.setCharacterSize(24);
    m_homeLabel.setColor(sf::Color::White);
    m_homeLabel.setString( "Home" );

    //End Screen Text Loading

    m_endTitleLabel.setFont(*m_font);
    m_endTitleLabel.setCharacterSize(24);
    m_endTitleLabel.setColor(sf::Color::Black);
    m_endTitleLabel.setString( "Your Score" );

    m_gameSpeedmultiplicatorLabel.setFont(*m_font);
    m_gameSpeedmultiplicatorLabel.setCharacterSize(24);
    m_gameSpeedmultiplicatorLabel.setColor(sf::Color::Black);
    m_gameSpeedmultiplicatorLabel.setString( "Game speed multiplicator" );

    m_gameSpeedmultiplicatorText.setFont(*m_font);
    m_gameSpeedmultiplicatorText.setCharacterSize(24);
    m_gameSpeedmultiplicatorText.setColor(sf::Color(86,103,97,255));
    m_gameSpeedmultiplicatorText.setString( "" );

    m_distanceLabel.setFont(*m_font);
    m_distanceLabel.setCharacterSize(24);
    m_distanceLabel.setColor(sf::Color::White);
    m_distanceLabel.setString( "Distance travelled" );

    m_CoinsCollectedNumberLabel.setFont(*m_font);
    m_CoinsCollectedNumberLabel.setCharacterSize(24);
    m_CoinsCollectedNumberLabel.setColor(sf::Color::Black);
    m_CoinsCollectedNumberLabel.setString( "Coins collected" );

    m_scoreLabel.setFont(*m_font);
    m_scoreLabel.setCharacterSize(24);
    m_scoreLabel.setColor(sf::Color::White);
    m_scoreLabel.setStyle(sf::Text::Bold);
    m_scoreLabel.setString( "Total score" );

    m_scoreText.setFont(*m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setColor(sf::Color::White);
    m_scoreText.setStyle(sf::Text::Bold);
    m_scoreText.setString( "" );
}


/********************************************
    Menu Text Syncing
*********************************************
    @author Arthur  @date 02/04
*********************************************/
void Text::syncMenuText(int width, int height)
{
    m_playButtonText.setPosition( width/2-30, height/1.42 );
    m_quitButtonText.setPosition( width/2-30, height/1.15 );
}


/********************************************
    Game Screen Syncing
*********************************************
    @author Arthur  @date 02/04
*********************************************/
void Text::syncGameText(GameModel *gameModel)
{
    m_playerLifeLabel.setPosition(40,545);
    m_distanceLabel.setPosition(530, 545);
    m_distanceText.setPosition(750,545);
    m_distanceText.setString( to_string(gameModel->getDistance() ) + " m" );
}


/********************************************
    Pause Screen Syncing
*********************************************
    @author Arthur  @date 02/04
*********************************************/
void Text::syncPauseText(GameModel *gameModel)
{
    m_distanceText.setPosition(80, 30);
    m_CoinsCollectedNumberText.setPosition(80, 70);
    m_CoinsCollectedNumberText.setColor(sf::Color(255,204,0,255));
    m_pauseResumeLabel.setPosition(80, 400);
    m_restartLabel.setPosition(80, 450);
    m_homeLabel.setPosition(80, 500);

    m_distanceText.setString( to_string(gameModel->getDistance() ) + " m" );
    m_CoinsCollectedNumberText.setString(to_string(gameModel->getNbCoinsCollected() ));

}

/********************************************
    End Screen Syncing
*********************************************
    @author Arthur  @date 02/04
*********************************************/
void Text::syncEndText(GameModel *gameModel)
{
    m_endTitleLabel.setPosition(400, 80);
    m_gameSpeedmultiplicatorLabel.setPosition(220, 170);
    m_gameSpeedmultiplicatorText.setPosition(580, 170);
    m_distanceLabel.setPosition(220, 207);
    m_distanceLabel.setColor(sf::Color::Black);
    m_distanceText.setPosition(580, 207);
    m_distanceText.setColor(sf::Color(86,103,97,255));
    m_CoinsCollectedNumberLabel.setPosition(220, 245);
    m_CoinsCollectedNumberText.setPosition(580, 245);
    m_CoinsCollectedNumberText.setColor(sf::Color(86,103,97,255));
    m_scoreLabel.setPosition(220,350);
    m_scoreText.setPosition(580,350);
    m_homeLabel.setPosition(80,535);
    m_restartLabel.setPosition(750,535);

    m_gameSpeedmultiplicatorText.setString(  to_string( gameModel->getGameSpeed() ));
    m_distanceText.setString(  to_string( gameModel->getDistance() ) + " m" );
    m_CoinsCollectedNumberText.setString( to_string( gameModel->getNbCoinsCollected() ) + "  X  20" );
    m_scoreText.setString( to_string( gameModel->getScore() ) );
}


/********************************************
    Menu Screen Drawing
*********************************************
    @author Arthur  @date 02/04
*********************************************/
void Text::drawMenuText(sf::RenderWindow *window)
{
    window->draw(m_playButtonText);
    window->draw(m_quitButtonText);
}


/********************************************
    Game Screen Drawing
*********************************************
    @author Arthur  @date 02/04
*********************************************/
void Text::drawGameText(sf::RenderWindow *window)
{
    window->draw(m_playerLifeLabel);
    window->draw(m_scoreText);
    window->draw(m_distanceLabel);
    window->draw(m_distanceText);
}


/********************************************
    Pause Screen Drawing
*********************************************
    @author Arthur  @date 02/04
*********************************************/
void Text::drawPauseText(sf::RenderWindow *window)
{
    window->draw(m_distanceText);
    window->draw(m_CoinsCollectedNumberText);
    window->draw(m_pauseResumeLabel);
    window->draw(m_restartLabel);
    window->draw(m_homeLabel);
}


/********************************************
    End Screen Drawing
*********************************************
    @author Arthur  @date 02/04
*********************************************/
void Text::drawEndText(sf::RenderWindow *window)
{
    window->draw(m_endTitleLabel);
    window->draw(m_gameSpeedmultiplicatorLabel);
    window->draw(m_gameSpeedmultiplicatorText);
    window->draw(m_distanceLabel);
    window->draw(m_distanceText);
    window->draw(m_CoinsCollectedNumberLabel);
    window->draw(m_CoinsCollectedNumberText);
    window->draw(m_scoreLabel);
    window->draw(m_scoreText);
    window->draw(m_homeLabel);
    window->draw(m_restartLabel);
}
