#include "GameView.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 26/03/16 - 25/01/17
 */
GameView::GameView(float w, float h, sf::RenderWindow *myWindow, TextHandler *text):
        View(w, h, myWindow, text), m_gameModel{nullptr},
        m_xPixelIntensity{1}, m_yPixelIntensity{1}
{
    loadImages();
    m_pixelShader = new PixelateEffect();

    if (!m_coinMusic.openFromFile(COINS_COLLECTED_MUSIC))
        cerr << "ERROR when loading music file: " << COINS_COLLECTED_MUSIC << endl;

    if (!m_destructedEnemiesMusic.openFromFile(ENEMIES_DESTRUCTED_MUSIC))
        cerr << "ERROR when loading music file: " << ENEMIES_DESTRUCTED_MUSIC << endl;
}


/**
 * Destructor
 * @author Arthur
 * @date 26/03/16 - 21/05/16
 */
GameView::~GameView()
{
    //=== Delete Game Element

    delete m_farSlBackground;
    delete m_farBgTransitionSprite;
    delete m_nearSlBackground;
    delete m_bottomBarSprite;
    delete m_lifeBoxSprite;
    delete m_remainingLifeSprite;
    delete m_stdEnemyAnimSprite;
    delete m_totemEnemyAnimSprite;
    delete m_blockEnemyAnimSprite;
    delete m_coinAnimSprite;
    delete m_PVPlusBonusAnimSprite;
    delete m_megaBonusAnimSprite;
    delete m_flyBonusAnimSprite;
    delete m_slowSpeedBonusAnimSprite;
    delete m_shieldBonusAnimSprite;
    delete m_shieldAnimSprite;
    delete m_pixelShader;
    for (auto it = m_MovableToGraphicElementMap.begin();
         it!=m_MovableToGraphicElementMap.end(); ++it )
        delete it->second;

    //=== Delete Pause and End Elements

    delete m_pauseBackgroundSprite;
    delete m_distanceIconSprite;
    delete m_endBackgroundSprite;
    delete m_resumeGameButton;
    delete m_restartGameButton;
    delete m_goToHomeButton;
    delete m_controlMusicButton;
    delete m_saveScoreButton;
}


//=== Setters

void GameView::setGameModel(GameModel *model)
{
    m_gameModel = model;

    //=== change default game music if in master mode

    string game_music;
    if ( m_gameModel->getDataBase()->getDifficulty() == EASY)
        game_music = GAME_NORMAL_THEME_MUSIC;
    else
        game_music = GAME_MASTER_THEME_MUSIC;

    if (!m_gameThemeMusic.openFromFile(game_music))
        cerr << "ERROR when loading music file: " << game_music << endl;
    else
    {
        handleMusic();
        m_gameThemeMusic.play();
        m_gameThemeMusic.setLoop(true);
    }

    //=== change ball skin if not default one

    if (m_gameModel->getDataBase()->getBallSkin() == "morphing")
    {
        std::vector<sf::IntRect> clipRect;
        for (int i=0; i<8; i++)
            clipRect.push_back(sf::IntRect(50*i,50,50,50));
        m_playerAnimSprite->setClipRectArray(clipRect);
    }
    else if (m_gameModel->getDataBase()->getBallSkin() == "capsule")
    {
        std::vector<sf::IntRect> clipRect;
        for (int i=0; i<8; i++)
            clipRect.push_back(sf::IntRect(50*i,100,50,50));
        m_playerAnimSprite->setClipRectArray(clipRect);
    }
}


/**
 * Image Loading
 * @author Arthur
 * @date 26/03/16 - 25/01/17
 */
void GameView::loadImages()
{
    //=== Initialize backgrounds

    m_farSlBackground = new SlidingBackground(1200, m_height, 1, DEFAULT_FAR_HILL_BACKGROUND);
    m_nearSlBackground = new SlidingBackground(1200, m_height, 2, DEFAULT_NEAR_HILL_BACKGROUND);

    m_farBgTransitionSprite = new GraphicElement(900, m_height, m_width, m_height, DEFAULT_FAR_T1_BACKGROUND);
    m_bottomBarSprite = new GraphicElement(0, 520, 1200, m_height, BOTTOM_BAR_IMAGE);

    m_pauseBackgroundSprite = new GraphicElement(0, 0, m_width, m_height, PAUSE_HILL_BACKGROUND);
    m_endBackgroundSprite = new GraphicElement(0, 0, m_width, m_height, END_SCREEN_BACKGROUND);


    //=== Initialize UI elements

    m_lifeBoxSprite = new GraphicElement(105, 535, 200, 100);
    m_lifeBoxSprite->setTextureFromImage(LIFE_BOX_IMAGE, sf::IntRect(0,0,300,50));

    m_remainingLifeSprite = new GraphicElement(107, 535, 300, 50);
    m_remainingLifeSprite->setTextureFromImage(LIFE_BOX_IMAGE, sf::IntRect(0,51,300,50));

    m_distanceIconSprite = new GraphicElement(30, 35, 25, 25);
    m_distanceIconSprite->setTextureFromImage(GAME_BUTTONS_IMAGE, sf::IntRect(0,150,50,50));
    m_distanceIconSprite->resize(25,25);


    //=== Initialize PLAYER

    std::vector<sf::IntRect> clipRect;
    for (int i=0; i<8; i++)
        clipRect.push_back(sf::IntRect(50*i,0,50,50));
    m_playerAnimSprite = new AnimatedGraphicElement(50, GAME_FLOOR, 30, 30, BALL_IMAGE, clipRect);
    m_playerAnimSprite->setOrigin(0,50);


    //=== Initialize ENEMIES

    std::vector<sf::IntRect> clipRectStdEnemy;
    for (int i=0; i<2; i++) clipRectStdEnemy.push_back(sf::IntRect(50*i,0,50,50));
    m_stdEnemyAnimSprite = new AnimatedGraphicElement(30, 135, 30, 30, ENEMIES_IMAGE, clipRectStdEnemy);
    m_stdEnemyAnimSprite->setOrigin(0,50);

    std::vector<sf::IntRect> clipRectTotemEnemy;
    for (int i=0; i<2; i++) clipRectTotemEnemy.push_back(sf::IntRect(50*i,0,50,150));
    m_totemEnemyAnimSprite = new AnimatedGraphicElement(m_width, GAME_FLOOR, 30, 90, ENEMIES_IMAGE,
                                                        clipRectTotemEnemy);
    m_totemEnemyAnimSprite->setOrigin(0,150);

    std::vector<sf::IntRect> clipRectBlockEnemy;
    for (int i=0; i<2; i++) clipRectBlockEnemy.push_back(sf::IntRect(50*i,150,50,50));
    m_blockEnemyAnimSprite = new AnimatedGraphicElement(50, 95, 50, 50, ENEMIES_IMAGE, clipRectBlockEnemy);
    m_blockEnemyAnimSprite->setOrigin(0,50);


    //=== Initialize COINS & BONUSES

    m_shieldAnimSprite = new GraphicElement(50, GAME_FLOOR, 40, 40);
    m_shieldAnimSprite->setTextureFromImage(SHIELD_IMAGE);
    m_shieldAnimSprite->setOrigin(0,50);

    std::vector<sf::IntRect> clipRect_coin;
    for (int i=0; i<5; i++) clipRect_coin.push_back(sf::IntRect(50*i,0,50,50));
    m_coinAnimSprite = new AnimatedGraphicElement(30, 95, 25, 25, BONUS_IMAGE, clipRect_coin);
    m_coinAnimSprite->setOrigin(0,50);

    std::vector<sf::IntRect> clipRect_pv;
    for (int i=0; i<5; i++)clipRect_pv.push_back(sf::IntRect(50*i,50,50,50));
    m_PVPlusBonusAnimSprite = new AnimatedGraphicElement(m_width, GAME_FLOOR, 25, 25, BONUS_IMAGE, clipRect_pv);
    m_PVPlusBonusAnimSprite->setOrigin(0,50);

    std::vector<sf::IntRect> clipRect_mega;
    for (int i=0; i<5; i++) clipRect_mega.push_back(sf::IntRect(50*i,100,50,50));
    m_megaBonusAnimSprite = new AnimatedGraphicElement(100, 50, 25, 25, BONUS_IMAGE, clipRect_mega);
    m_megaBonusAnimSprite->setOrigin(0,50);

    std::vector<sf::IntRect> clipRect_fly;
    for (int i=0; i<5; i++) clipRect_fly.push_back(sf::IntRect(50*i,150,50,50));
    m_flyBonusAnimSprite = new AnimatedGraphicElement(100, 50, 25, 25, BONUS_IMAGE, clipRect_fly);
    m_flyBonusAnimSprite->setOrigin(0,50);

    std::vector<sf::IntRect> clipRect_slow;
    for (int i=0; i<5; i++) clipRect_slow.push_back(sf::IntRect(50*i,200,50,50));
    m_slowSpeedBonusAnimSprite = new AnimatedGraphicElement(100, 50, 25, 25, BONUS_IMAGE, clipRect_slow);
    m_slowSpeedBonusAnimSprite->setOrigin(0,50);

    std::vector<sf::IntRect> clipRect_shield;
    for (int i=0; i<5; i++) clipRect_shield.push_back(sf::IntRect(50*i,250,50,50));
    m_shieldBonusAnimSprite = new AnimatedGraphicElement(100, 50, 25, 25, BONUS_IMAGE, clipRect_shield);
    m_shieldBonusAnimSprite->setOrigin(0,50);


    //=== Initialize buttons

    std::vector<sf::IntRect> clipRect_resume;
    clipRect_resume.push_back(sf::IntRect(0, 0, 50, 50));
    clipRect_resume.push_back(sf::IntRect(50, 0, 50, 50));
    m_resumeGameButton = new Button(PAUSE_FORM_X, 355, 25, 25, "pause_resume",
                                    GAME_BUTTONS_IMAGE, clipRect_resume);
    m_resumeGameButton->resize(25,25);
    m_resumeGameButton->setLabelPosition(RIGHT);

    std::vector<sf::IntRect> clipRect_restart;
    clipRect_restart.push_back(sf::IntRect(0, 50, 50, 50));
    clipRect_restart.push_back(sf::IntRect(50, 50, 50, 50));
    m_restartGameButton = new Button(PAUSE_FORM_X, 405, 25, 25, "pause_restart",
                                     GAME_BUTTONS_IMAGE, clipRect_restart);
    m_restartGameButton->resize(25,25);
    m_restartGameButton->setLabelPosition(RIGHT);


    std::vector<sf::IntRect> clipRect_home;
    clipRect_home.push_back(sf::IntRect(0, 100, 50, 50));
    clipRect_home.push_back(sf::IntRect(50, 100, 50, 50));
    m_goToHomeButton = new Button(PAUSE_FORM_X, 455, 25, 25, "pause_go_to_home",
                                  GAME_BUTTONS_IMAGE, clipRect_home);
    m_goToHomeButton->resize(25,25);
    m_goToHomeButton->setLabelPosition(RIGHT);

    std::vector<sf::IntRect> clipRect_music;
    clipRect_music.push_back(sf::IntRect(0, 200, 50, 50));
    clipRect_music.push_back(sf::IntRect(50, 200, 50, 50));
    m_controlMusicButton = new Button(PAUSE_FORM_X, 535, 25, 25, "pause_music",
                                      GAME_BUTTONS_IMAGE, clipRect_music);
    m_controlMusicButton->resize(25,25);
    m_controlMusicButton->setLabelPosition(RIGHT);

    std::vector<sf::IntRect> clipRect_save;
    clipRect_save.push_back(sf::IntRect(0, 179, 150, 40));
    clipRect_save.push_back(sf::IntRect(151, 179, 150, 40));
    m_saveScoreButton = new Button(730, 350, m_width / 2 - 75, 430, "end_save_button",
                                   RECT_BUTTONS_IMAGE, clipRect_save);
}


/**
 * Link mElements with gElements
 * @author Arthur
 * @date 18/03/16 - 21/05/16
 */
void GameView::linkElements()
{
    set<MovableElement*>::const_iterator it;
    for ( it = m_gameModel->getNewMElementsArray().begin();
          it != m_gameModel->getNewMElementsArray().end(); ++it)
    {
        assert((*it) != nullptr);

        if ( (*it)->getType() == PLAYER )
            m_MovableToGraphicElementMap[*it] = m_playerAnimSprite;
        else if ( (*it)->getType() == STANDARD_ENEMY )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_stdEnemyAnimSprite);
        else if ( (*it)->getType() == TOTEM_ENEMY )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_totemEnemyAnimSprite);
        else if ( (*it)->getType() == BLOCK_ENEMY )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_blockEnemyAnimSprite);
        else if ( (*it)->getType() == COIN )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_coinAnimSprite);
        else if ( (*it)->getType() == PV_PLUS_BONUS )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_PVPlusBonusAnimSprite);
        else if ( (*it)->getType() == MEGA_BONUS )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_megaBonusAnimSprite);
        else if ( (*it)->getType() == FLY_BONUS )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_flyBonusAnimSprite);
        else if ( (*it)->getType() == SLOW_SPEED_BONUS )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_slowSpeedBonusAnimSprite);
        else if ( (*it)->getType() == SHIELD_BONUS )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_shieldBonusAnimSprite);
    }
    m_gameModel->clearNewMovableElementList();
}


/**
 * Create seamless transition between zones
 * @author Arthur
 * @date 25/04/16 - 02/01/17
 */
void GameView::handleZonesTransition()
{
    if (m_gameModel->getTransitionStatus())
    {
        //Set background speed and position
        m_farBgTransitionSprite->setPosition(m_farBgTransitionSprite->getPosition().x - TRANSITION_SPEED, 0);
        m_farSlBackground->setSpeed(TRANSITION_SPEED);
        m_nearSlBackground->decreaseAlpha(5);
        if ( m_nearSlBackground->getAlpha() == 0)
            m_nearSlBackground->setSpeed(0);
        else
            m_nearSlBackground->setSpeed(TRANSITION_SPEED);

        //Update zone background image and position at half transition
        if (m_farBgTransitionSprite->getPosition().x  <= 5
            && m_farBgTransitionSprite->getPosition().x  >= -5)
        {
            if (m_gameModel->getCurrentZone() == HILL)
            {
                m_farSlBackground->setTextureFromImage(DEFAULT_FAR_PLAIN_BACKGROUND);
                m_nearSlBackground->setTextureFromImage(DEFAULT_NEAR_PLAIN_BACKGROUND);
            }
            else
            {
                m_farSlBackground->setTextureFromImage(DEFAULT_FAR_HILL_BACKGROUND);
                m_nearSlBackground->setTextureFromImage(DEFAULT_NEAR_HILL_BACKGROUND);
            }

            m_farSlBackground->setPosition(-300, 0);
            m_nearSlBackground->setPosition(0, 0);
        }

        //Update pixel creation of near background from 3/4 transition to end transition
        if ( m_farBgTransitionSprite->getPosition().x < m_width/2 && m_xPixelIntensity >=0)
        {
            m_xPixelIntensity -= 0.009;
            m_yPixelIntensity -= 0.009;
            m_pixelShader->update(m_xPixelIntensity, m_yPixelIntensity);
        }

        //Finish transition
        if (m_farBgTransitionSprite->getPosition().x
            + m_farBgTransitionSprite->getLocalBounds().width <= 0)
        {
            //Update Transition status
            m_gameModel->setTransitionStatus(false);
            m_gameModel->setTransitionPossibleStatus(false);

            //Set current zone
            if (m_gameModel->getCurrentZone() == HILL)
                m_gameModel->setCurrentZone(PLAIN);
            else
                m_gameModel->setCurrentZone(HILL);
        }
    }
    else
    {
        m_farSlBackground->setSpeed((float) (0.5 * m_gameModel->getGameSpeed()));
        m_nearSlBackground->setSpeed(m_gameModel->getGameSpeed() );
        m_nearSlBackground->setAlpha(255);

        if (m_gameModel->getTransitionPossibleStatus()
            && m_farSlBackground->getSeparationPositionX() > m_width - 100)
        {
            m_gameModel->setTransitionStatus(true);
            m_xPixelIntensity = 1;
            m_yPixelIntensity = 1;
            m_farBgTransitionSprite->setPosition(m_farSlBackground->getPosition().x + 1200, 0);

            if (m_gameModel->getCurrentZone() == HILL)
            {
                m_pixelShader->load(DEFAULT_NEAR_T1_BACKGROUND);
                m_farBgTransitionSprite->setTextureFromImage(DEFAULT_FAR_T1_BACKGROUND);
            }
            else
            {
                m_pixelShader->load(DEFAULT_NEAR_T2_BACKGROUND);
                m_farBgTransitionSprite->setTextureFromImage(DEFAULT_FAR_T2_BACKGROUND);
            }
        }
    }
}


/**
 * Update gElements
 * @author Arthur
 * @date 6/03/16 - 25/01/17
 */
void GameView::updateElements()
{
    if (m_gameModel->getGameState() == RUNNING ||
        m_gameModel->getGameState() == RUNNING_SLOWLY)
    {
        //=== Handle Transitions between zones

        handleZonesTransition();

        //=== Update Game Elements

        m_farSlBackground->sync();
        m_nearSlBackground->sync();

        m_remainingLifeSprite->resize(3*m_gameModel->getPlayer()->getLife(), 50);

        std::map<MovableElement*, GraphicElement*>::iterator it;
        for(it = m_MovableToGraphicElementMap.begin() ; it != m_MovableToGraphicElementMap.end() ; ++it)
        {
            m_gameModel->moveMovableElement(it->first);

            float position_x = (it->first)->getPosX();
            float position_y = (it->first)->getPosY();

            it->second->setPosition( position_x, position_y );
            it->second->sync();
            it->second->resize(it->first->getWidth(), it->first->getHeight() );
        }

        //=== Update shield sprite

        m_shieldAnimSprite->setPosition( m_gameModel->getPlayer()->getPosX()-5,
                                         m_gameModel->getPlayer()->getPosY()+5 );
        m_shieldAnimSprite->sync();
        m_shieldAnimSprite->resize(40,40);

    }
    else if ( m_gameModel->getGameState() == PAUSED )
    {
        if (m_gameModel->getCurrentZone() == HILL)
            m_pauseBackgroundSprite->setTextureFromImage(PAUSE_HILL_BACKGROUND);
        else
            m_pauseBackgroundSprite->setTextureFromImage(PAUSE_PLAIN_BACKGROUND);

        m_resumeGameButton->sync(m_gameModel->getDataBase());
        m_restartGameButton->sync(m_gameModel->getDataBase());
        m_restartGameButton->setLabelPosition(RIGHT);
        m_goToHomeButton->sync(m_gameModel->getDataBase());
        m_controlMusicButton->sync(m_gameModel->getDataBase());
        m_coinAnimSprite->sync();
        m_coinAnimSprite->resize(20,20);
        m_stdEnemyAnimSprite->sync();
        m_stdEnemyAnimSprite->resize(20,20);
    }
    else //GAME OVER
    {
        m_goToHomeButton->sync(m_gameModel->getDataBase());
        m_goToHomeButton->resize(30,30);
        m_goToHomeButton->setPosition(30, 535);

        m_coinAnimSprite->resize(25,25);
        m_coinAnimSprite->setPosition( (float)(m_width / 2.4), 565);

        m_restartGameButton->sync(m_gameModel->getDataBase());
        m_restartGameButton->resize(30,30);
        m_restartGameButton->setPosition(840, 535);
        m_restartGameButton->setLabelPosition(LEFT);

        m_saveScoreButton->sync(m_gameModel->getDataBase());
        m_saveScoreButton->setPositionSelfCentered(m_width/2, 430);
    }
}


/**
 * Delete gElement
 * @author Arthur
 * @date 12/03/16 - 20/03/16
 */
void GameView::deleteElements()
{
    std::map<MovableElement *, GraphicElement *>::iterator it =
            m_MovableToGraphicElementMap.begin();
    bool found = false;
    while (!found && it!=m_MovableToGraphicElementMap.end() )
    {
        if ((it->first)->isColliding())
        {
            if ( (it->first)->getType() == COIN )
                m_coinMusic.play();

            if ( (it->first)->getType() == STANDARD_ENEMY
                || (it->first)->getType() == TOTEM_ENEMY
                || (it->first)->getType() ==BLOCK_ENEMY  )
                m_destructedEnemiesMusic.play();

            delete it->second;
            m_MovableToGraphicElementMap.erase(it);
            found = true;
        }
        else
            ++it;
    }
}


/**
 * Synchronization function
 * @author Arthur
 * @date 26/03/16 - 25/12/16
 */
void GameView::synchronize()
{

    if (m_gameModel->getGameState() == RUNNING ||
        m_gameModel->getGameState() == RUNNING_SLOWLY)
    {
        linkElements();
        deleteElements();
        updateElements();
        m_textHandler->syncGameText(m_gameModel->getBonusTimeout());
    }
    else if (m_gameModel->getGameState() == PAUSED)
    {
        updateElements();
        m_textHandler->syncPauseText();
        sf::sleep(sf::milliseconds(180)); //limit CPU usage
    }
    else //GAME OVER
    {
        //=== audio ending

        if(m_gameThemeMusic.getStatus() == sf::Music::Status::Playing )
            m_gameThemeMusic.stop();

        //=== Buttons & text update

        updateElements();
        m_textHandler->syncEndText((int)m_gameModel->getGameSpeed());

    }
}


/**
 * Handles music settings
 * @author Arthur
 * @date 25/01/17
 */
void GameView::handleMusic()
{
    //change music volume
    if (m_gameModel->getDataBase()->isGameMusicEnabled())
    {
        std::vector<sf::IntRect> clipRect;
        clipRect.push_back(sf::IntRect(0,200,50,50));
        clipRect.push_back(sf::IntRect(50,200,50,50));
        m_controlMusicButton->setClipRectArray(clipRect);
        m_gameThemeMusic.setVolume(100);
        m_coinMusic.setVolume(100);
        m_destructedEnemiesMusic.setVolume(100);
    }
    else
    {
        std::vector<sf::IntRect> clipRect;
        clipRect.push_back(sf::IntRect(0,250,50,50));
        clipRect.push_back(sf::IntRect(50,250,50,50));
        m_controlMusicButton->setClipRectArray(clipRect);
        m_gameThemeMusic.setVolume(0);
        m_coinMusic.setVolume(0);
        m_destructedEnemiesMusic.setVolume(0);
    }
}


/**
 * GameView Drawing
 * @author Arthur
 * @date 26/03/16 - 25/12/16
 */
void GameView::draw() const
{
    m_window->clear();

    if (m_gameModel->getGameState() == RUNNING ||
        m_gameModel->getGameState() == RUNNING_SLOWLY)
    {
        //=== Standalone GraphicElements drawing

        m_farSlBackground->draw(m_window);

        if (m_gameModel->getTransitionStatus())
        {
            m_window->draw(*m_farBgTransitionSprite);
            if ( m_farBgTransitionSprite->getPosition().x < m_width/2 )
                m_window->draw(*m_pixelShader);
        }

        m_nearSlBackground->draw(m_window);
        m_window->draw(*m_bottomBarSprite);
        m_window->draw(*m_remainingLifeSprite);
        m_window->draw(*m_lifeBoxSprite);

        //=== Array's GraphicElements drawing

        for(auto it = m_MovableToGraphicElementMap.begin() ;
            it != m_MovableToGraphicElementMap.end() ; ++it)
        {
            it->second->draw(m_window);
        }

        if ( m_gameModel->getPlayer()->getState() == SHIELD)
            m_window->draw(*m_shieldAnimSprite);

        //=== TextHandler drawing

        m_textHandler->drawGameText(m_window);
    }
    else if (m_gameModel->getGameState() == PAUSED)
    {
        //=== Background drawing & GraphicElements drawing

        m_window->draw(*m_pauseBackgroundSprite);
        m_window->draw(*m_distanceIconSprite);
        m_window->draw(*m_coinAnimSprite);
        m_window->draw(*m_stdEnemyAnimSprite);
        m_resumeGameButton->draw(m_window);
        m_restartGameButton->draw(m_window);
        m_goToHomeButton->draw(m_window);
        m_controlMusicButton->draw(m_window);

        //=== TextHandler drawing

        m_textHandler->drawPauseText(m_window);
    }
    else //GAME OVER
    {
        //=== Background drawing & Buttons drawing

        m_window->draw(*m_endBackgroundSprite);
        m_window->draw(*m_coinAnimSprite);
        m_restartGameButton->draw(m_window);
        m_goToHomeButton->draw(m_window);
        m_saveScoreButton->draw(m_window);

        //=== TextHandler drawing

        m_textHandler->drawEndText(m_window);
    }

    m_window->display();
}


/**
 * Events treating
 * @author Arthur, Florian
 * @date 21/02/16 - 25/12/16
 */
bool GameView::treatEvents()
{
    bool result = false;

    if(m_window->isOpen())
    {
        result = true;

        if (m_gameModel->getGameState() == RUNNING ||
            m_gameModel->getGameState() == RUNNING_SLOWLY)
        {
            //=== Player Controls in Game Screen

            if (KEYBOARD_LEFT)
                m_gameModel->getPlayer()->controlPlayerMovements(MOVE_LEFT);

            else if (KEYBOARD_RIGHT)
                m_gameModel->getPlayer()->controlPlayerMovements(MOVE_RIGHT);

            if (KEYBOARD_JUMP)
                m_gameModel->getPlayer()->setJumpState(true);
        }

        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if  (event.type == sf::Event::Closed)
            {
                m_model->setAppState(QUIT);
                m_window->close();
                result = false;
            }

            //=== Handle open/quit pause

            if (m_gameModel->getGameState() != OVER && event.type == sf::Event::KeyPressed
                && event.key.code == sf::Keyboard::Escape)
            {
                if (m_gameModel->getGameState() == RUNNING ||
                    m_gameModel->getGameState() == RUNNING_SLOWLY)
                {
                    m_gameModel->setGameState(PAUSED);
                    m_gameThemeMusic.pause();
                }
                else
                {
                    m_gameModel->setGameState(RUNNING_SLOWLY);
                    m_gameThemeMusic.play();
                }
            }

            if (event.type == sf::Event::KeyReleased)
                m_gameModel->getPlayer()->setDecelerationState(true);

            //=== Pause Screen

            if (m_gameModel->getGameState() == PAUSED)
            {
                if (MOUSE_LEFT_PRESSED_EVENT)
                {
                    if (m_resumeGameButton->contains(MOUSE_POSITION) )
                        m_resumeGameButton->setPressed(true);

                    else if (m_restartGameButton->contains(MOUSE_POSITION) )
                        m_restartGameButton->setPressed(true);

                    else if (m_goToHomeButton->contains(MOUSE_POSITION) )
                        m_goToHomeButton->setPressed(true);

                    else if (m_controlMusicButton->contains(MOUSE_POSITION) )
                        m_controlMusicButton->setPressed(true);

                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    m_resumeGameButton->setPressed(false);
                    m_restartGameButton->setPressed(false);
                    m_goToHomeButton->setPressed(false);
                    m_controlMusicButton->setPressed(false);

                    if (m_resumeGameButton->contains(MOUSE_POSITION) )
                    {
                        m_gameModel->setGameState(RUNNING_SLOWLY);
                        if(m_gameThemeMusic.getStatus() == sf::Music::Status::Paused)
                            m_gameThemeMusic.play();
                    }
                    else if (m_restartGameButton->contains(MOUSE_POSITION) )
                    {
                        m_model->setAppState(RESET_GAME);
                        result = false;
                    }
                    else if (m_goToHomeButton->contains(MOUSE_POSITION) )
                    {
                        m_model->setAppState(MENU);
                        result = false;
                    }
                    else if (m_controlMusicButton->contains(MOUSE_POSITION) )
                    {
                        m_gameModel->getDataBase()->setGameMusic(!m_gameModel->getDataBase()->isGameMusicEnabled());
                        handleMusic();
                    }
                }
            }
            else if (m_gameModel->getGameState() == OVER)
            {
                if (MOUSE_LEFT_PRESSED_EVENT)
                {
                    if (m_restartGameButton->contains(MOUSE_POSITION) )
                        m_restartGameButton->setPressed(true);

                    else if (m_goToHomeButton->contains(MOUSE_POSITION) )
                        m_goToHomeButton->setPressed(true);

                    else if (m_saveScoreButton->contains(MOUSE_POSITION) )
                        m_saveScoreButton->setPressed(true);
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    m_restartGameButton->setPressed(false);
                    m_goToHomeButton->setPressed(false);
                    m_saveScoreButton->setPressed(false);

                    if (m_restartGameButton->contains(MOUSE_POSITION) )
                    {
                        m_model->setAppState(RESET_GAME);
                        result = false;
                    }
                    else if (m_goToHomeButton->contains(MOUSE_POSITION) )
                    {
                        m_model->setAppState(MENU);
                        result = false;
                    }
                    else if (m_saveScoreButton->contains(MOUSE_POSITION) )
                    {
                        m_saveScoreButton->hide();
                        m_model->getDataBase()->saveCurrentGame();
                    }
                }
            }
        }
    }
    return result;
}
