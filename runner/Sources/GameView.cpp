#include "GameView.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 26/03 - 22/05
*********************************************/
GameView::GameView(float w, float h, sf::RenderWindow *mywindow, Text *text):
    View(w, h, mywindow, text), m_gameModel{nullptr},
    m_xPixelIntensity{1}, m_yPixelIntensity{1}, m_isMusicEnabled{true}
{
    loadImages();
    m_pixelShader = new PixelateEffect();

    if (!m_coinMusic.openFromFile(COINS_COLLECTED_MUSIC))
            cerr << "ERROR when loading music file: " << COINS_COLLECTED_MUSIC << endl;

    if (!m_destructedEnemiesMusic.openFromFile(ENEMIES_DESTRUCTED_MUSIC))
            cerr << "ERROR when loading music file: " << ENEMIES_DESTRUCTED_MUSIC << endl;
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 26/03 - 21/05
*********************************************/
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


/********************************************
   Setters
*********************************************
    @author Arthur  @date 27/03 - 20/05
*********************************************/
void GameView::setGameModel(GameModel *model)
{
    m_gameModel = model;

    //=== change default game music if in master mode

    string game_music;
    if ( m_gameModel->getDifficulty() == NORMAL_DIFFICULTY)
        game_music = GAME_NORMAL_THEME_MUSIC;
    else
        game_music = GAME_MASTER_THEME_MUSIC;

    if (!m_gameThemeMusic.openFromFile(game_music))
        cerr << "ERROR when loading music file: " << game_music << endl;
    else
    {
        m_gameThemeMusic.play();
        m_gameThemeMusic.setLoop(true);
    }

    //=== change ball skin if not default one

    if (m_gameModel->getDataBase()->getBallSkin() == "morphing")
    {
        std::vector<sf::IntRect> clip_rects;
        for (int i=0; i<8; i++)
            clip_rects.push_back(sf::IntRect(50*i,50,50,50));
        m_playerAnimSprite->setClipRectArray(clip_rects);
    }
    else if (m_gameModel->getDataBase()->getBallSkin() == "capsule")
    {
        std::vector<sf::IntRect> clip_rects;
        for (int i=0; i<8; i++)
            clip_rects.push_back(sf::IntRect(50*i,100,50,50));
        m_playerAnimSprite->setClipRectArray(clip_rects);
    }
}


/********************************************
    Image Loading
*********************************************
    @author Arthur  @date 26/03 - 27/04
*********************************************/
void GameView::loadImages()
{
    if (!m_farBackgroundTexture.loadFromFile(DEFAULT_FAR_HILL_BACKGROUND))
        cerr << "ERROR when loading image file: " << DEFAULT_FAR_HILL_BACKGROUND << endl;
    else
    {
        m_farBackgroundTexture.setSmooth(true);
        m_farSlBackground = new SlidingBackground(m_farBackgroundTexture, 1200, m_height, 1);
    }

    if (!m_farBgTransitionTexture.loadFromFile(DEFAULT_FAR_T1_BACKGROUND))
        cerr << "ERROR when loading image file: " << DEFAULT_FAR_T1_BACKGROUND << endl;
    else
    {
        m_farBgTransitionTexture.setSmooth(true);
        m_farBgTransitionSprite = new GraphicElement(m_farBgTransitionTexture, 900, m_height, m_width, m_height);
    }

    if (!m_nearBackgroundTexture.loadFromFile(DEFAULT_NEAR_HILL_BACKGROUND))
        cerr << "ERROR when loading image file: " << DEFAULT_NEAR_HILL_BACKGROUND << endl;
    else
    {
        m_nearBackgroundTexture.setSmooth(true);
        m_nearSlBackground = new SlidingBackground(m_nearBackgroundTexture, 1200, m_height, 2);
    }

    if (!m_bottomBarTexture.loadFromFile(BOTTOM_BAR_IMAGE))
        cerr << "ERROR when loading image file: " << BOTTOM_BAR_IMAGE << endl;
    else
    {
        m_bottomBarTexture.setSmooth(true);
        m_bottomBarSprite = new GraphicElement(m_bottomBarTexture, 0, 520, 1200, m_height);
    }

    if (!m_lifeBoxTexture.loadFromFile(LIFE_BOX_IMAGE))
        cerr << "ERROR when loading image file: " << LIFE_BOX_IMAGE << endl;
    else
    {
        m_lifeBoxTexture.setSmooth(true);
        m_lifeBoxSprite = new GraphicElement(m_lifeBoxTexture, 105, 535, 200, 100);
    }

    if (!m_remainingLifeTexture.loadFromFile(LIFE_BOX_IMAGE))
        cerr << "ERROR when loading image file: " << LIFE_BOX_IMAGE << endl;
    else
    {
        m_remainingLifeTexture.setSmooth(true);
        m_remainingLifeSprite = new GraphicElement(m_remainingLifeTexture, 107, 535, 300, 50);
    }

    if (!m_playerTexture.loadFromFile(BALL_IMAGE) )
        cerr << "ERROR when loading image file: " << BALL_IMAGE << endl;
    else
    {
        std::vector<sf::IntRect> clip_rects;
        for (int i=0; i<8; i++)
            clip_rects.push_back(sf::IntRect(50*i,0,50,50));

        m_playerTexture.setSmooth(true);
        m_playerAnimSprite = new AnimatedGraphicElement(m_playerTexture, 50, GAME_FLOOR, 30, 30, clip_rects);
        m_playerAnimSprite->setOrigin(0,50);
    }

    if (!m_enemyTexture.loadFromFile(ENEMIES_IMAGE))
        cerr << "ERROR when loading image file: " << ENEMIES_IMAGE << endl;
    else
    {
        m_enemyTexture.setSmooth(true);

        std::vector<sf::IntRect> clip_rects_st_enemy;
        for (int i=0; i<2; i++) clip_rects_st_enemy.push_back(sf::IntRect(50*i,0,50,50));
        m_stdEnemyAnimSprite = new AnimatedGraphicElement(m_enemyTexture, 30, 135,30,30, clip_rects_st_enemy);
        m_stdEnemyAnimSprite->setOrigin(0,50);

        std::vector<sf::IntRect> clip_rects_to_enemy;
        for (int i=0; i<2; i++) clip_rects_to_enemy.push_back(sf::IntRect(50*i,0,50,150));
        m_totemEnemyAnimSprite = new AnimatedGraphicElement(m_enemyTexture,
                                                            m_width, GAME_FLOOR,30,90, clip_rects_to_enemy);
        m_totemEnemyAnimSprite->setOrigin(0,150);

        std::vector<sf::IntRect> clip_rects_bl_enemy;
        for (int i=0; i<2; i++) clip_rects_bl_enemy.push_back(sf::IntRect(50*i,150,50,50));
        m_blockEnemyAnimSprite = new AnimatedGraphicElement(m_enemyTexture, 50, 95,50,50, clip_rects_bl_enemy);
        m_blockEnemyAnimSprite->setOrigin(0,50);
    }

    if (!m_shieldTexture.loadFromFile(SHIELD_IMAGE))
        cerr << "ERROR when loading image file: " << SHIELD_IMAGE << endl;
    else
    {
        m_shieldTexture.setSmooth(true);
        m_shieldAnimSprite = new GraphicElement(m_shieldTexture, 50, GAME_FLOOR, 40, 40);
        m_shieldAnimSprite->setOrigin(0,50);
    }

    if (!m_bonusTexture.loadFromFile(BONUS_IMAGE))
        cerr << "ERROR when loading image file: " << BONUS_IMAGE << endl;
    else
    {
        m_bonusTexture.setSmooth(true);

        std::vector<sf::IntRect> clip_rects_coin;
        for (int i=0; i<5; i++) clip_rects_coin.push_back(sf::IntRect(50*i,0,50,50));
        m_coinAnimSprite = new AnimatedGraphicElement(m_bonusTexture, 30, 95, 25, 25, clip_rects_coin);
        m_coinAnimSprite->setOrigin(0,50);

        std::vector<sf::IntRect> clip_rects_pv;
        for (int i=0; i<5; i++)clip_rects_pv.push_back(sf::IntRect(50*i,50,50,50));
        m_PVPlusBonusAnimSprite = new AnimatedGraphicElement(m_bonusTexture,
                                                             m_width, GAME_FLOOR, 25, 25, clip_rects_pv);
        m_PVPlusBonusAnimSprite->setOrigin(0,50);

        std::vector<sf::IntRect> clip_rects_mega;
        for (int i=0; i<5; i++) clip_rects_mega.push_back(sf::IntRect(50*i,100,50,50));
        m_megaBonusAnimSprite = new AnimatedGraphicElement(m_bonusTexture, 100, 50, 25, 25, clip_rects_mega);
        m_megaBonusAnimSprite->setOrigin(0,50);

        std::vector<sf::IntRect> clip_rects_fly;
        for (int i=0; i<5; i++) clip_rects_fly.push_back(sf::IntRect(50*i,150,50,50));
        m_flyBonusAnimSprite = new AnimatedGraphicElement(m_bonusTexture, 100, 50, 25, 25, clip_rects_fly);
        m_flyBonusAnimSprite->setOrigin(0,50);

        std::vector<sf::IntRect> clip_rects_slow;
        for (int i=0; i<5; i++) clip_rects_slow.push_back(sf::IntRect(50*i,200,50,50));
        m_slowSpeedBonusAnimSprite = new AnimatedGraphicElement(m_bonusTexture, 100, 50, 25, 25, clip_rects_slow);
        m_slowSpeedBonusAnimSprite->setOrigin(0,50);

        std::vector<sf::IntRect> clip_rects_shield;
        for (int i=0; i<5; i++) clip_rects_shield.push_back(sf::IntRect(50*i,250,50,50));
        m_shieldBonusAnimSprite = new AnimatedGraphicElement(m_bonusTexture, 100, 50, 25, 25, clip_rects_shield);
        m_shieldBonusAnimSprite->setOrigin(0,50);
    }


    if (!m_gameButtonsTexture.loadFromFile(GAME_BUTTONS_IMAGE) )
        cerr << "ERROR when loading image file: " << GAME_BUTTONS_IMAGE << endl;
    else
    {
        m_gameButtonsTexture.setSmooth(true);

        std::vector<sf::IntRect> clip_rects_resume;
        clip_rects_resume.push_back(sf::IntRect(0, 0, 50, 50));
        clip_rects_resume.push_back(sf::IntRect(50, 0, 50, 50));
        m_resumeGameButton = new Button(clip_rects_resume,
                m_gameButtonsTexture, PAUSE_FORM_X, 355, 20, 20, false);
        m_resumeGameButton->resize(20,20);

        std::vector<sf::IntRect> clip_rects_restart;
        clip_rects_restart.push_back(sf::IntRect(0, 50, 50, 50));
        clip_rects_restart.push_back(sf::IntRect(50, 50, 50, 50));
        m_restartGameButton = new Button(clip_rects_restart,
                m_gameButtonsTexture, PAUSE_FORM_X, 405, 20, 20, false);
        m_restartGameButton->resize(20,20);

        std::vector<sf::IntRect> clip_rects_home;
        clip_rects_home.push_back(sf::IntRect(0, 100, 50, 50));
        clip_rects_home.push_back(sf::IntRect(50, 100, 50, 50));
        m_goToHomeButton = new Button(clip_rects_home,
                m_gameButtonsTexture, PAUSE_FORM_X, 455, 20, 20, false);
        m_goToHomeButton->resize(20,20);

        std::vector<sf::IntRect> clip_rects_music;
        clip_rects_music.push_back(sf::IntRect(0, 200, 50, 50));
        clip_rects_music.push_back(sf::IntRect(50, 200, 50, 50));
        m_controlMusicButton = new Button(clip_rects_music,
                m_gameButtonsTexture, PAUSE_FORM_X, 535, 20, 20, false);
        m_controlMusicButton->resize(20,20);
    }

    if (!m_gameRectButtonTexture.loadFromFile(RECT_BUTTONS_IMAGE) )
        cerr << "ERROR when loading image file: " << RECT_BUTTONS_IMAGE << endl;
    else
    {
        m_gameRectButtonTexture.setSmooth(true);

        std::vector<sf::IntRect> clip_rects_save;
        clip_rects_save.push_back(sf::IntRect(0, 179, 150, 40));
        clip_rects_save.push_back(sf::IntRect(151, 179, 150, 40));
        m_saveScoreButton = new Button(clip_rects_save,
                    m_gameRectButtonTexture, 730, 350, m_width/2-75, 430, false);
    }


    if (!m_distanceIconTexture.loadFromFile(GAME_BUTTONS_IMAGE, sf::IntRect(0,150,50,50)) )
        cerr << "ERROR when loading image file: " << GAME_BUTTONS_IMAGE << endl;
    else
    {
        m_distanceIconTexture.setSmooth(true);
        m_distanceIconSprite = new GraphicElement(m_distanceIconTexture, 30, 35, 20, 20);
        m_distanceIconSprite->resize(20,20);
    }


    if (!m_pauseBackgroundTexture.loadFromFile(PAUSE_HILL_BACKGROUND))
        cerr << "ERROR when loading image file: " << PAUSE_PLAIN_BACKGROUND << endl;
    else
    {
        m_pauseBackgroundTexture.setSmooth(true);
        m_pauseBackgroundSprite = new GraphicElement(m_pauseBackgroundTexture, 0, 0, m_width, m_height);
    }


    if (!m_endBackgroundTexture.loadFromFile(ENDSCREEN_BACKGROUND))
        cerr << "ERROR when loading image file: " << ENDSCREEN_BACKGROUND << endl;
    else
    {
        m_endBackgroundTexture.setSmooth(true);
        m_endBackgroundSprite = new GraphicElement(m_endBackgroundTexture, 0, 0, m_width, m_height);
    }
}


/********************************************
    Link mElements with gElements
*********************************************
    @author Arthur  @date 18/03 - 21/05
*********************************************/
void GameView::linkElements()
{
    set<MovableElement*>::const_iterator it;
    for ( it = m_gameModel->getNewMElementsArray().begin();
          it != m_gameModel->getNewMElementsArray().end(); ++it)
    {
        assert((*it) != nullptr);

        if ( (*it)->getType() == PLAYER )
            m_MovableToGraphicElementMap[*it] = m_playerAnimSprite;
        else if ( (*it)->getType() == STANDARDENEMY )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_stdEnemyAnimSprite);
        else if ( (*it)->getType() == TOTEMENEMY )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_totemEnemyAnimSprite);
        else if ( (*it)->getType() == BLOCKENEMY )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_blockEnemyAnimSprite);
        else if ( (*it)->getType() == COIN )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_coinAnimSprite);
        else if ( (*it)->getType() == PVPLUSBONUS )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_PVPlusBonusAnimSprite);
        else if ( (*it)->getType() == MEGABONUS )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_megaBonusAnimSprite);
        else if ( (*it)->getType() == FLYBONUS )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_flyBonusAnimSprite);
        else if ( (*it)->getType() == SLOWSPEEDBONUS )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_slowSpeedBonusAnimSprite);
        else if ( (*it)->getType() == SHIELDBONUS )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_shieldBonusAnimSprite);
    }
    m_gameModel->clearNewMovableElementList();
}


/********************************************
    Create seamless transition between zones
*********************************************
    @author Arthur  @date 25/04 - 07/05
*********************************************/
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
                m_farBackgroundTexture.loadFromFile(DEFAULT_FAR_PLAIN_BACKGROUND);
                m_nearBackgroundTexture.loadFromFile(DEFAULT_NEAR_PLAIN_BACKGROUND);
            }
            else
            {
                m_farBackgroundTexture.loadFromFile(DEFAULT_FAR_HILL_BACKGROUND);
                m_nearBackgroundTexture.loadFromFile(DEFAULT_NEAR_HILL_BACKGROUND);
            }

            m_farSlBackground->setPosition(-300, 0);
            m_nearSlBackground->setPosition(0, 0);
        }

        //Update pixel creation of near backgound from 3/4 transition to end transition
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
                m_farBgTransitionTexture.loadFromFile(DEFAULT_FAR_T1_BACKGROUND);
            }
            else
            {
                m_pixelShader->load(DEFAULT_NEAR_T2_BACKGROUND);
                m_farBgTransitionTexture.loadFromFile(DEFAULT_FAR_T2_BACKGROUND);
            }
        }
    }
}


/********************************************
    Update gElements
*********************************************
    @author Arthur  @date 6/03 - 22/05
*********************************************/
void GameView::updateElements()
{
     if (!m_gameModel->getPauseState() && !m_gameModel->getEndState())
     {
         //=== Handle Transitions between zones

         handleZonesTransition();

        //=== Update Game Elements

        m_farSlBackground->sync();
        m_nearSlBackground->sync();

        m_remainingLifeTexture.loadFromFile( REMAINING_LIFE,
        sf::IntRect( 3*( 100-m_gameModel->getPlayer()->getLife() ), 0, 300, 50 ) );

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
    else if ( m_gameModel->getPauseState() )
    {
        if (m_gameModel->getCurrentZone() == 1)
                m_pauseBackgroundTexture.loadFromFile(PAUSE_HILL_BACKGROUND);
            else
                m_pauseBackgroundTexture.loadFromFile(PAUSE_PLAIN_BACKGROUND);

        m_resumeGameButton->sync();
        m_restartGameButton->sync();
        m_goToHomeButton->sync();
        m_controlMusicButton->sync();
        m_coinAnimSprite->sync();
        m_coinAnimSprite->resize(20,20);
        m_stdEnemyAnimSprite->sync();
        m_stdEnemyAnimSprite->resize(20,20);
    }
    else if ( m_gameModel->getEndState() )
    {
        m_goToHomeButton->sync();
        m_goToHomeButton->resize(30,30);
        m_goToHomeButton->setPosition(30, 535);

        m_coinAnimSprite->resize(25,25);
        m_coinAnimSprite->setPosition( (float)(m_width / 2.4), 563);

        m_restartGameButton->sync();
        m_restartGameButton->resize(30,30);
        m_restartGameButton->setPosition(840, 535);

        m_saveScoreButton->sync();
        if (!m_gameModel->getSaveStatus())
            m_saveScoreButton->setPosition(m_width+5, m_height+5);
        else
            m_saveScoreButton->setPosition(m_width/2 -
                m_saveScoreButton->getGlobalBounds().width/2, 430);
    }
}


/********************************************
    Delete gElement
*********************************************
    @author Arthur  @date 12/03 - 20/03
*********************************************/
void GameView::deleteElements()
{
    std::map<MovableElement *, GraphicElement *>::iterator it =
                m_MovableToGraphicElementMap.begin();
    bool found = false;
    while (!found && it!=m_MovableToGraphicElementMap.end() )
    {
        if ((it->first)->getCollisionState())
        {
            if ( (it->first)->getType() == COIN )
                m_coinMusic.play();

            if ( (it->first)->getType() == STANDARDENEMY
                || (it->first)->getType() == TOTEMENEMY
                || (it->first)->getType() ==BLOCKENEMY  )
                m_destructedEnemiesMusic.play();

            delete it->second;
            m_MovableToGraphicElementMap.erase(it);
            found = true;
        }
        else
            ++it;
    }
}


/********************************************
    Synchronization function
*********************************************
    @author Arthur  @date 26/03 - 03/05
*********************************************/
void GameView::synchronize()
{

    if (!m_gameModel->getPauseState()&& !m_gameModel->getEndState()) //GAME
    {
        linkElements(); //Link new mElements with gElements
        deleteElements(); //Elements deleting if not used anymore
        updateElements(); //Elements update
        m_text->syncGameText(m_gameModel->getBonusTimeout()); //Text update
    }
    else if (m_gameModel->getPauseState()) //PAUSE
    {
        updateElements(); //Elements update
        m_text->syncPauseText(); //Text update
        sf::sleep(sf::milliseconds(2*NEXT_STEP_DELAY)); //limit CPU usage
    }
    else if (m_gameModel->getEndState())//END
    {
        //=== Music ending

        if(m_gameThemeMusic.getStatus() == sf::Music::Status::Playing )
            m_gameThemeMusic.stop();

        //=== Buttons & text update

        updateElements(); //Buttons update
        m_text->syncEndText(m_gameModel->getSaveStatus(),
                            (int)m_gameModel->getGameSpeed()); //Text update

    }
}


/********************************************
    GameView Drawing
*********************************************
    @author Arthur  @date 26/03 - 22/05
*********************************************/
void GameView::draw() const
{
    m_window->clear();

    if (!m_gameModel->getPauseState() && !m_gameModel->getEndState() ) //GAME
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

        //=== Text drawing

        m_text->drawGameText(m_window);

    }
    else if (m_gameModel->getPauseState()) //PAUSE
    {
        //=== Background drawing & GraphicElements drawing

        m_window->draw(*m_pauseBackgroundSprite);
        m_window->draw(*m_distanceIconSprite);
        m_window->draw(*m_coinAnimSprite);
        m_window->draw(*m_stdEnemyAnimSprite);
        m_window->draw(*m_resumeGameButton);
        m_window->draw(*m_restartGameButton);
        m_window->draw(*m_goToHomeButton);
        m_window->draw(*m_controlMusicButton);

        //=== Text drawing

        m_text->drawPauseText(m_window);

    }
    else if (m_gameModel->getEndState()) //END
    {
        //=== Background drawing & Buttons drawing

        m_window->draw(*m_endBackgroundSprite);
        m_window->draw(*m_restartGameButton);
        m_window->draw(*m_coinAnimSprite);
        m_window->draw(*m_goToHomeButton);
        if (m_gameModel->getSaveStatus())
            m_window->draw(*m_saveScoreButton);

        //=== Text drawing

        m_text->drawEndText(m_window);

    }

    m_window->display();
}


/********************************************
    Events treating
*********************************************
    @author Arthur  @date 21/02 - 22/05
    @author Florian @date 21/02 - 06/05
*********************************************/
bool GameView::treatEvents()
{
    bool result = false;

    if(m_window->isOpen())
    {
        result = true;

        if (!m_gameModel->getPauseState())
        {
            //=== Player Controls in Game Screen

            if ( KEYBOARD_LEFT )
            {
                m_gameModel->getPlayer()->controlPlayerMovements(MOVE_LEFT);
            }
            else if ( KEYBOARD_RIGHT )
            {
                m_gameModel->getPlayer()->controlPlayerMovements(MOVE_RIGHT);
            }
            if ( KEYBOARD_JUMP )
            {
                m_gameModel->getPlayer()->setJumpState(true);
            }
        }

        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if  (event.type == sf::Event::Closed)
            {
                m_model->setGameState(false);
                m_window->close();
                result = false;
            }

            //=== Handle open /quit pause

            if (!m_gameModel->getEndState() && event.type == sf::Event::KeyPressed
                && event.key.code == sf::Keyboard::Escape)
            {
                m_gameModel->setPauseState(!m_gameModel->getPauseState() );

                //Change Music status
                if(m_gameThemeMusic.getStatus() == sf::Music::Status::Playing )
                    m_gameThemeMusic.pause();
                else if(m_gameThemeMusic.getStatus() == sf::Music::Status::Paused)
                    m_gameThemeMusic.play();
            }
            if (event.type == sf::Event::KeyReleased)
                m_gameModel->getPlayer()->setDecelerationState(true);

            //=== Pause Screen

            if (m_gameModel->getPauseState())
            {
                if (MOUSE_LEFT_PRESSED_EVENT)
                {
                    if ( m_resumeGameButton->IS_POINTED || m_text->getResumeText()->IS_POINTED )
                    {
                        m_resumeGameButton->setPressedState(true);
                    }
                    else if ( m_restartGameButton->IS_POINTED || m_text->getRestartText()->IS_POINTED )
                    {
                        m_restartGameButton->setPressedState(true);
                    }
                    else if ( m_goToHomeButton->IS_POINTED || m_text->getHomeText()->IS_POINTED )
                    {
                        m_goToHomeButton->setPressedState(true);
                    }
                    else if ( m_controlMusicButton->IS_POINTED )
                    {
                        m_controlMusicButton->setPressedState(true);
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    m_resumeGameButton->setPressedState(false);
                    m_restartGameButton->setPressedState(false);
                    m_goToHomeButton->setPressedState(false);
                    m_controlMusicButton->setPressedState(false);

                    if ( m_resumeGameButton->IS_POINTED || m_text->getResumeText()->IS_POINTED )
                    {
                        m_gameModel->setPauseState(false);
                        if(m_gameThemeMusic.getStatus() == sf::Music::Status::Paused)
                            m_gameThemeMusic.play();
                    }
                    else if ( m_restartGameButton->IS_POINTED || m_text->getRestartText()->IS_POINTED )
                    {
                        m_gameModel->setPauseState(false);
                        m_model->setGameState(false);
                        m_model->setResetGameState(true);
                        result = false;
                    }
                    else if ( m_goToHomeButton->IS_POINTED || m_text->getHomeText()->IS_POINTED )
                    {
                        m_gameModel->setPauseState(false);
                        m_model->setGameState(false);
                        m_model->setMenuState(true);
                        result = false;
                    }
                    else if ( m_controlMusicButton->IS_POINTED )
                    {
                        m_isMusicEnabled = !m_isMusicEnabled;
                        //change music volume
                        if (m_isMusicEnabled)
                        {
                            std::vector<sf::IntRect> clip_rects;
                            clip_rects.push_back(sf::IntRect(0,200,50,50));
                            clip_rects.push_back(sf::IntRect(50,200,50,50));
                            m_controlMusicButton->setClipRectArray(clip_rects);
                            m_gameThemeMusic.setVolume(100);
                            m_coinMusic.setVolume(100);
                            m_destructedEnemiesMusic.setVolume(100);
                        }
                        else
                        {
                            std::vector<sf::IntRect> clip_rects;
                            clip_rects.push_back(sf::IntRect(0,250,50,50));
                            clip_rects.push_back(sf::IntRect(50,250,50,50));
                            m_controlMusicButton->setClipRectArray(clip_rects);
                            m_gameThemeMusic.setVolume(0);
                            m_coinMusic.setVolume(0);
                            m_destructedEnemiesMusic.setVolume(0);
                        }
                    }
                }
            }

            //=== End Screen

            else if (m_gameModel->getEndState())
            {
                if (MOUSE_LEFT_PRESSED_EVENT)
                {
                    if ( m_restartGameButton->IS_POINTED || m_text->getRestartText()->IS_POINTED )
                    {
                        m_restartGameButton->setPressedState(true);
                    }
                    else if ( m_goToHomeButton->IS_POINTED || m_text->getHomeText()->IS_POINTED )
                    {
                        m_goToHomeButton->setPressedState(true);
                    }
                    else if ( m_saveScoreButton->IS_POINTED )
                    {
                        m_saveScoreButton->setPressedState(true);
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    m_restartGameButton->setPressedState(false);
                    m_goToHomeButton->setPressedState(false);
                    m_saveScoreButton->setPressedState(false);

                    if ( m_restartGameButton->IS_POINTED || m_text->getRestartText()->IS_POINTED )
                    {
                        m_gameModel->setEndState(false);
                        m_model->setGameState(false);
                        m_model->setResetGameState(true);
                        result = false;
                    }
                    else if ( m_goToHomeButton->IS_POINTED || m_text->getHomeText()->IS_POINTED )
                    {
                        m_gameModel->setEndState(false);
                        m_model->setGameState(false);
                        m_model->setMenuState(true);
                        result = false;
                    }
                    else if ( m_saveScoreButton->IS_POINTED )
                    {
                        m_gameModel->setSaveStatus(false);
                        m_model->getDataBase()->saveCurrentGame();
                    }
                }
            }
        }
    }
    return result;
}
