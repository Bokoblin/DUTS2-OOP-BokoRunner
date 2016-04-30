#include "../header/GameView.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 26/03 - 28/04
*********************************************/
GameView::GameView(float w, float h, sf::RenderWindow *mywindow, Text *text):
    View(w, h, mywindow, text), m_gameModel{nullptr},
    m_xPixelIntensity{1}, m_yPixelIntensity{1}
{
    loadImages();
    m_lb = new Leaderboard;
    m_pixelShader = new Pixelate();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 26/03 - 28/04
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
    delete m_playerAnimSprite;
    delete m_stdEnemyAnimSprite;
    delete m_totemEnemyAnimSprite;
    delete m_blockEnemyAnimSprite;
    delete m_coinAnimSprite;
    delete m_PVPlusBonusAnimSprite;
    delete m_megaBonusAnimSprite;
    delete m_flyBonusAnimSprite;
    delete m_slowSpeedBonusAnimSprite;
    delete m_pixelShader;

    //=== Delete Pause and End Elements

    delete m_pauseBackgroundSprite;
    delete m_distanceIconSprite;
    delete m_resumeGameButton;
    delete m_restartGameButton;
    delete m_goToHomeButton;
    delete m_endBackgroundSprite;
    delete m_saveScoreButton;
}


/********************************************
   Setters
*********************************************
    @author Arthur  @date 27/03
*********************************************/
void GameView::setGameModel(GameModel *model)
{
    m_gameModel = model;
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
        m_playerAnimSprite = new AnimatedGraphicElement(m_playerTexture, 50, GAME_FLOOR, 30, 30, clip_rects, 8);
        m_playerAnimSprite->setOrigin(0,50);
    }

    if (!m_enemyTexture.loadFromFile(ENEMIES_IMAGE))
        cerr << "ERROR when loading image file: " << ENEMIES_IMAGE << endl;
    else
    {
        m_enemyTexture.setSmooth(true);

        std::vector<sf::IntRect> clip_rects_st_enemy;
        for (int i=0; i<4; i++) clip_rects_st_enemy.push_back(sf::IntRect(50*i,0,50,50));
        m_stdEnemyAnimSprite = new AnimatedGraphicElement(m_enemyTexture, 30, 135,30,30, clip_rects_st_enemy, 2);
        m_stdEnemyAnimSprite->setOrigin(0,50);

        std::vector<sf::IntRect> clip_rects_to_enemy;
        for (int i=0; i<4; i++) clip_rects_to_enemy.push_back(sf::IntRect(50*i,0,50,150));
        m_totemEnemyAnimSprite = new AnimatedGraphicElement(m_enemyTexture, m_width, GAME_FLOOR,30,90, clip_rects_to_enemy, 2);
        m_totemEnemyAnimSprite->setOrigin(0,150);

        std::vector<sf::IntRect> clip_rects_bl_enemy;
        for (int i=0; i<4; i++) clip_rects_bl_enemy.push_back(sf::IntRect(50*i,150,50,50));
        m_blockEnemyAnimSprite = new AnimatedGraphicElement(m_enemyTexture, 50, 95,50,50, clip_rects_bl_enemy, 2);
        m_blockEnemyAnimSprite->setOrigin(0,50);
    }

    if (!m_bonusTexture.loadFromFile(BONUS_IMAGE))
        cerr << "ERROR when loading image file: " << BONUS_IMAGE << endl;
    else
    {
        m_bonusTexture.setSmooth(true);

        std::vector<sf::IntRect> clip_rects_coin;
        for (int i=0; i<5; i++) clip_rects_coin.push_back(sf::IntRect(50*i,0,50,50));
        m_coinAnimSprite = new AnimatedGraphicElement(m_bonusTexture, 30, 95, 25, 25, clip_rects_coin, 5);
        m_coinAnimSprite->setOrigin(0,50);

        std::vector<sf::IntRect> clip_rects_pv;
        for (int i=0; i<5; i++)clip_rects_pv.push_back(sf::IntRect(50*i,50,50,50));
        m_PVPlusBonusAnimSprite = new AnimatedGraphicElement(m_bonusTexture, m_width, GAME_FLOOR, 25, 25, clip_rects_pv, 5);
        m_PVPlusBonusAnimSprite->setOrigin(0,50);

        std::vector<sf::IntRect> clip_rects_mega;
        for (int i=0; i<5; i++) clip_rects_mega.push_back(sf::IntRect(50*i,100,50,50));
        m_megaBonusAnimSprite = new AnimatedGraphicElement(m_bonusTexture, 100, 50, 25, 25, clip_rects_mega, 5);
        m_megaBonusAnimSprite->setOrigin(0,50);

        std::vector<sf::IntRect> clip_rects_fly;
        for (int i=0; i<5; i++) clip_rects_fly.push_back(sf::IntRect(50*i,150,50,50));
        m_flyBonusAnimSprite = new AnimatedGraphicElement(m_bonusTexture, 100, 50, 25, 25, clip_rects_fly, 5);
        m_flyBonusAnimSprite->setOrigin(0,50);

        std::vector<sf::IntRect> clip_rects_slow;
        for (int i=0; i<5; i++) clip_rects_slow.push_back(sf::IntRect(50*i,200,50,50));
        m_slowSpeedBonusAnimSprite = new AnimatedGraphicElement(m_bonusTexture, 100, 50, 25, 25, clip_rects_slow, 5);
        m_slowSpeedBonusAnimSprite->setOrigin(0,50);
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
                    m_gameButtonsTexture, 30, 405, 20, 20, false);
        m_resumeGameButton->resize(20,20);

        std::vector<sf::IntRect> clip_rects_restart;
        clip_rects_restart.push_back(sf::IntRect(0, 50, 50, 50));
        clip_rects_restart.push_back(sf::IntRect(50, 50, 50, 50));
        m_restartGameButton = new Button(clip_rects_restart,
                    m_gameButtonsTexture, 30, 455, 20, 20, false);
        m_restartGameButton->resize(20,20);

        std::vector<sf::IntRect> clip_rects_home;
        clip_rects_home.push_back(sf::IntRect(0, 100, 50, 50));
        clip_rects_home.push_back(sf::IntRect(50, 100, 50, 50));
        m_goToHomeButton = new Button(clip_rects_home,
                    m_gameButtonsTexture, 30, 505, 20, 20, false);
        m_goToHomeButton->resize(20,20);

        std::vector<sf::IntRect> clip_rects_save;
        clip_rects_save.push_back(sf::IntRect(51, 200, 50, 50));
        clip_rects_save.push_back(sf::IntRect(0, 200, 50, 50));
        m_saveScoreButton = new Button(clip_rects_save,
                    m_gameButtonsTexture, 730, 350, m_width, m_height, false);
    }


    if (!m_distanceIconTexture.loadFromFile(GAME_BUTTONS_IMAGE, sf::IntRect(0,150,50,50)) )
        cerr << "ERROR when loading image file: " << GAME_BUTTONS_IMAGE << endl;
    else
    {
        m_distanceIconTexture.setSmooth(true);
        m_distanceIconSprite = new GraphicElement(m_distanceIconTexture, 30, 35, 20, 20);
        m_distanceIconSprite->resize(20,20);
    }


    if (!m_pauseBackgroundTexture.loadFromFile(PAUSE_BGND_IMAGE))
        cerr << "ERROR when loading image file: " << PAUSE_BGND_IMAGE << endl;
    else
    {
        m_pauseBackgroundTexture.setSmooth(true);
        m_pauseBackgroundSprite = new GraphicElement(m_pauseBackgroundTexture, 0, 0, m_width, m_height);
    }


    if (!m_endBackgroundTexture.loadFromFile(END_BGND_IMAGE))
        cerr << "ERROR when loading image file: " << END_BGND_IMAGE << endl;
    else
    {
        m_endBackgroundTexture.setSmooth(true);
        m_endBackgroundSprite = new GraphicElement(m_endBackgroundTexture, 0, 0, m_width, m_height);
    }
}


/********************************************
    Link mElements with gElements
*********************************************
    @author Arthur  @date 18/03 - 11/04
*********************************************/
void GameView::linkElements()
{
    set<MovableElement*>::const_iterator it;
    for ( it = m_gameModel->getNewMElementsArray().begin(); it != m_gameModel->getNewMElementsArray().end(); ++it)
    {
        assert((*it) != nullptr);

        if ( (*it)->getType() == 0 )
            m_MovableToGraphicElementMap[*it] = m_playerAnimSprite;
        else if ( (*it)->getType() == 1 )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_stdEnemyAnimSprite);
        else if ( (*it)->getType() == 2 )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_totemEnemyAnimSprite);
        else if ( (*it)->getType() == 3 )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_blockEnemyAnimSprite);
        else if ( (*it)->getType() == 4 )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_coinAnimSprite);
        else if ( (*it)->getType() == 5 )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_PVPlusBonusAnimSprite);
        else if ( (*it)->getType() == 6 )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_megaBonusAnimSprite);
        else if ( (*it)->getType() == 7 )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_flyBonusAnimSprite);
        else if ( (*it)->getType() == 8 )
            m_MovableToGraphicElementMap[*it] = new AnimatedGraphicElement(*m_slowSpeedBonusAnimSprite);
    }
    m_gameModel->clearNewMovableElementList();
}


/********************************************
    Update gElements
*********************************************
    @author Arthur  @date 6/03 - 30/04
*********************************************/
void GameView::updateElements()
{
    //=== Handle Transitions between zones

    if ( m_gameModel->getTransitionStatus() == true)
    {
        //Set backgrouns speed and position
        m_farBgTransitionSprite->setPosition(m_farBgTransitionSprite->getPosition().x - TRANSITION_SPEED, 0);
        m_farSlBackground->setSpeed(TRANSITION_SPEED);
        m_nearSlBackground->setSpeed(0);

        //Update zone background image and position at half transition
        if (m_farBgTransitionSprite->getPosition().x  <= 5 && m_farBgTransitionSprite->getPosition().x  >= -5)
        {
            if (m_gameModel->getCurrentZone() == 1)
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
            if (m_gameModel->getCurrentZone() == 1)
                m_pixelShader->load(DEFAULT_NEAR_T1_BACKGROUND);
            else
                m_pixelShader->load(DEFAULT_NEAR_T2_BACKGROUND);
            m_xPixelIntensity -= 0.009;
            m_yPixelIntensity -= 0.009;
            m_pixelShader->update(clock.getElapsedTime().asSeconds(), m_xPixelIntensity, m_yPixelIntensity);
        }

        //Finish transition
        if (m_farBgTransitionSprite->getPosition().x + m_farBgTransitionSprite->getLocalBounds().width <= 0)
        {
            //Update Transition status
            m_gameModel->setTransitionStatus(false);
            m_gameModel->setTransitionPossibleStatus(false);

            //Set current zone
            if (m_gameModel->getCurrentZone() == 1)
                m_gameModel->setCurrentZone(2);
            else
                m_gameModel->setCurrentZone(1);
        }
    }
    else
    {
        m_farSlBackground->setSpeed( (m_gameModel->getGameSpeed() + m_gameModel->getDifficulty() )/2);
        m_nearSlBackground->setSpeed(m_gameModel->getGameSpeed() + m_gameModel->getDifficulty() );

        if ( m_gameModel->getTransitionPossibleStatus() == true && m_farSlBackground->getSeparationPositionX() > m_width-100)
        {
            m_gameModel->setTransitionStatus(true);
            m_xPixelIntensity = 1;
            m_yPixelIntensity = 1;
            m_farBgTransitionSprite->setPosition(m_farSlBackground->getPosition().x +1200, 0);

            if (m_gameModel->getCurrentZone() == 1)
                m_farBgTransitionTexture.loadFromFile(DEFAULT_FAR_T1_BACKGROUND);
            else
                m_farBgTransitionTexture.loadFromFile(DEFAULT_FAR_T2_BACKGROUND);
        }
    }

    //=== Update Elements

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
        if ( (it->first)->getCollisionState() == true )
        {
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
    @author Arthur  @date 26/03 - 27/04
*********************************************/
void GameView::synchronize()
{

    if (m_gameModel->getPauseState() == false && m_gameModel->getEndState() == false )
    {
        //=== Link new mElements with gElements

        linkElements();

        //=== Elements deleting if not used anymore

        deleteElements();

        //=== Elements update

        updateElements();

        //=== Text update

        m_text->syncGameMainText(m_gameModel);

    }
    else if (m_gameModel->getPauseState() == true)
    {
        //=== Elements update

        m_resumeGameButton->sync();
        m_restartGameButton->sync();
        m_goToHomeButton->sync();
        m_coinAnimSprite->sync();
        m_coinAnimSprite->resize(20,20);
        m_stdEnemyAnimSprite->sync();
        m_stdEnemyAnimSprite->resize(20,20);

        //=== Text update

        m_text->syncGamePauseText(m_gameModel);

    }
    else if (m_gameModel->getEndState() == true )
    {
        //=== Buttons update

        m_goToHomeButton->sync();
        m_goToHomeButton->resize(30,30);
        m_goToHomeButton->setPosition(30, 535);

        m_restartGameButton->sync();
        m_restartGameButton->resize(30,30);
        m_restartGameButton->setPosition(840, 535);

        m_saveScoreButton->sync();
        m_saveScoreButton->resize(40,40);
        if ( m_gameModel->getScoreSavableStatus() == false)
            m_saveScoreButton->setPosition(m_width+5, m_height+5);

        //=== Text update

        m_text->syncGameEndText(m_gameModel);
    }
}


/********************************************
    GameView Drawing
*********************************************
    @author Arthur  @date 26/03 - 28/04
*********************************************/
void GameView::draw() const
{
    m_window->clear();

    if (m_gameModel->getPauseState() == false && m_gameModel->getEndState() == false )
    {
        //=== Standalone GraphicElements drawing

        m_farSlBackground->draw(m_window);

        if ( m_gameModel->getTransitionStatus() == true)
        {
            m_window->draw(*m_farBgTransitionSprite);
            m_window->draw(*m_pixelShader);
        }
        else
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

        //=== Text drawing

        m_text->drawGameText(m_window);

    }
    else if (m_gameModel->getPauseState() == true)
    {
        //=== Background drawing & GraphicElements drawing

        m_window->draw(*m_pauseBackgroundSprite);
        m_window->draw(*m_distanceIconSprite);
        m_window->draw(*m_coinAnimSprite);
        m_window->draw(*m_stdEnemyAnimSprite);
        m_window->draw(*m_resumeGameButton);
        m_window->draw(*m_restartGameButton);
        m_window->draw(*m_goToHomeButton);

        //=== Text drawing

        m_text->drawPauseText(m_window);

    }
    else if (m_gameModel->getEndState() == true )
    {
        //=== Background drawing & Buttons drawing

        m_window->draw(*m_endBackgroundSprite);
        m_window->draw(*m_restartGameButton);
        m_window->draw(*m_goToHomeButton);
        if ( m_gameModel->getScoreSavableStatus() == true)
            m_window->draw(*m_saveScoreButton);

        //=== Text drawing

        m_text->drawEndText(m_window);

    }

    m_window->display();
}


/********************************************
    Events treating
*********************************************
    @author Arthur  @date 21/02 - 19/04
    @author Florian @date 21/02 - 10/04
*********************************************/
bool GameView::treatEvents()
{
    bool result = false;

    if(m_window->isOpen())
    {
        result = true;

        if (m_gameModel->getPauseState() == false)
        {
            //=== Player Controls in Game Screen

            if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
                  || sf::Keyboard::isKeyPressed(sf::Keyboard::Left ) )  )
            {
                m_gameModel->getPlayer()->controlPlayerMovements(true);
            }
            else if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::Right ) )  )
            {
                m_gameModel->getPlayer()->controlPlayerMovements(false);
            }
            if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
                        || sf::Keyboard::isKeyPressed(sf::Keyboard::Space ) ) )
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
            if ( m_gameModel->getEndState() == false && event.type == sf::Event::KeyPressed
                        && event.key.code == sf::Keyboard::Escape)
            {
                m_gameModel->setPauseState(!m_gameModel->getPauseState() );
            }
            if (event.type == sf::Event::KeyReleased)
                m_gameModel->getPlayer()->setDecelerationState(true);

            //=== Pause Screen

            if (m_gameModel->getPauseState() == true)
            {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    if ( m_resumeGameButton->getGlobalBounds().contains(MOUSE_POSITION) ||
                            m_text->getResumeText()->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_resumeGameButton->setPressedState(true);
                    }
                    else if ( m_restartGameButton->getGlobalBounds().contains(MOUSE_POSITION) ||
                              m_text->getRestartText()->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_restartGameButton->setPressedState(true);
                    }
                    else if ( m_goToHomeButton->getGlobalBounds().contains(MOUSE_POSITION) ||
                              m_text->getHomeText()->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_goToHomeButton->setPressedState(true);
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    m_resumeGameButton->setPressedState(false);
                    m_restartGameButton->setPressedState(false);
                    m_goToHomeButton->setPressedState(false);

                    if ( m_resumeGameButton->getGlobalBounds().contains(MOUSE_POSITION) ||
                            m_text->getResumeText()->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_gameModel->setPauseState(false);
                    }
                    else if ( m_restartGameButton->getGlobalBounds().contains(MOUSE_POSITION) ||
                              m_text->getRestartText()->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_gameModel->setPauseState(false);
                        m_model->setGameState(false);
                        m_model->setResetGameState(true);
                        result = false;
                    }
                    else if ( m_goToHomeButton->getGlobalBounds().contains(MOUSE_POSITION) ||
                              m_text->getHomeText()->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_gameModel->setPauseState(false);
                        m_model->setGameState(false);
                        m_model->setMenuState(true);
                        result = false;
                    }
                }
            }

            //=== End Screen

            else if (m_gameModel->getEndState() == true)
            {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    if ( m_restartGameButton->getGlobalBounds().contains(MOUSE_POSITION) ||
                            m_text->getRestartText()->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_restartGameButton->setPressedState(true);
                    }
                    else if ( m_goToHomeButton->getGlobalBounds().contains(MOUSE_POSITION) ||
                              m_text->getHomeText()->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_goToHomeButton->setPressedState(true);
                    }
                    else if ( m_saveScoreButton->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_saveScoreButton->setPressedState(true);
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    m_restartGameButton->setPressedState(false);
                    m_goToHomeButton->setPressedState(false);
                    m_saveScoreButton->setPressedState(false);

                    if ( m_restartGameButton->getGlobalBounds().contains(MOUSE_POSITION) ||
                            m_text->getRestartText()->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_gameModel->setEndState(false);
                        m_model->setGameState(false);
                        m_model->setResetGameState(true);
                        result = false;
                    }
                    else if ( m_goToHomeButton->getGlobalBounds().contains(MOUSE_POSITION) ||
                              m_text->getHomeText()->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_gameModel->setEndState(false);
                        m_model->setGameState(false);
                        m_model->setMenuState(true);
                        result = false;
                    }
                    else if ( m_saveScoreButton->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_gameModel->setScoreSavableStatus(false);
                        m_lb->loadVectorFromFile();
                        m_lb->addEntryToVector(m_gameModel->getScore() );
                        m_lb->loadFileFromVector();
                    }
                }
            }
        }
    }
    return result;
}
