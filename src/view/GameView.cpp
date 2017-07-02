#include "GameView.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 26/03/16 - 29/01/17
 */
GameView::GameView(sf::RenderWindow *myWindow, TextHandler *textHandler, GameModel *gameModel) :
        AbstractView(myWindow, textHandler), m_game{gameModel},
        m_xPixelIntensity{1}, m_yPixelIntensity{1}
{
    loadImages();
    m_pixelShader = new PixelShader();

    //=== change default game music if in master mode

    string game_music;
    if (m_game->getDataBase()->getDifficulty() == EASY)
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

    if (m_game->getDataBase()->getBallSkin() == "morphing")
    {
        std::vector<sf::IntRect> clipRect;
        for (int i=0; i<8; i++)
            clipRect.push_back(sf::IntRect(50*i, 50, 50, 50));
        m_playerSprite->setClipRectArray(clipRect);
    }
    else if (m_game->getDataBase()->getBallSkin() == "capsule")
    {
        std::vector<sf::IntRect> clipRect;
        for (int i=0; i<8; i++)
            clipRect.push_back(sf::IntRect(50*i, 100, 50, 50));
        m_playerSprite->setClipRectArray(clipRect);
    }

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

    delete m_farScrollingBackground;
    delete m_farTransitionBackground;
    delete m_nearScrollingBackground;
    delete m_bottomBarImage;
    delete m_lifeBoxImage;
    delete m_remainingLifeImage;
    delete m_stdEnemySprite;
    delete m_totemEnemySprite;
    delete m_blockEnemySprite;
    delete m_coinSprite;
    delete m_PVPlusBonusSprite;
    delete m_megaBonusSprite;
    delete m_flyBonusSprite;
    delete m_slowSpeedBonusSprite;
    delete m_shieldBonusSprite;
    delete m_shieldImage;
    delete m_pixelShader;
    for (auto it = m_movableElementToSpriteMap.begin();
         it!=m_movableElementToSpriteMap.end(); ++it)
        delete it->second;

    //=== Delete Pause and End Elements

    delete m_pauseBackground;
    delete m_distanceIcon;
    delete m_endBackground;
    delete m_resumeGameButton;
    delete m_restartGameButton;
    delete m_goToHomeButton;
    delete m_controlMusicButton;
    delete m_saveScoreButton;
}


/**
 * Image Loading
 * @author Arthur
 * @date 26/03/16 - 25/01/17
 */
void GameView::loadImages()
{
    //=== Initialize backgrounds

    m_farScrollingBackground = new ScrollingBackground(1200, m_height, 1, DEFAULT_FAR_HILL_BACKGROUND);
    m_nearScrollingBackground = new ScrollingBackground(1200, m_height, 2, DEFAULT_NEAR_HILL_BACKGROUND);

    m_farTransitionBackground = new GraphicElement(900, m_height, m_width, m_height, DEFAULT_FAR_T1_BACKGROUND);
    m_bottomBarImage = new GraphicElement(0, 520, 1200, m_height, BOTTOM_BAR_IMAGE);

    m_pauseBackground = new GraphicElement(0, 0, m_width, m_height, PAUSE_HILL_BACKGROUND);
    m_endBackground = new GraphicElement(0, 0, m_width, m_height, END_SCREEN_BACKGROUND);


    //=== Initialize UI elements

    m_lifeBoxImage = new GraphicElement(105, 535, 200, 100);
    m_lifeBoxImage->setTextureFromImage(LIFE_BOX_IMAGE, sf::IntRect(0, 0, 300, 50));

    m_remainingLifeImage = new GraphicElement(107, 535, 300, 50);
    m_remainingLifeImage->setTextureFromImage(LIFE_BOX_IMAGE, sf::IntRect(0, 51, 300, 50));

    m_distanceIcon = new GraphicElement(30, 35, 25, 25);
    m_distanceIcon->setTextureFromImage(GAME_BUTTONS_IMAGE, sf::IntRect(0, 150, 50, 50));
    m_distanceIcon->resize(25, 25);


    //=== Initialize PLAYER

    std::vector<sf::IntRect> clipRect;
    for (int i=0; i<8; i++)
        clipRect.push_back(sf::IntRect(50*i, 0, 50, 50));
    m_playerSprite = new Sprite(50, GAME_FLOOR, 30, 30, BALL_IMAGE, clipRect);
    m_playerSprite->setOrigin(0, 50);


    //=== Initialize ENEMIES

    std::vector<sf::IntRect> clipRectStdEnemy;
    for (int i=0; i<2; i++) clipRectStdEnemy.push_back(sf::IntRect(50*i, 0, 50, 50));
    m_stdEnemySprite = new Sprite(30, 135, 30, 30, ENEMIES_IMAGE, clipRectStdEnemy);
    m_stdEnemySprite->setOrigin(0, 50);

    std::vector<sf::IntRect> clipRectTotemEnemy;
    for (int i=0; i<2; i++) clipRectTotemEnemy.push_back(sf::IntRect(50*i, 0, 50, 150));
    m_totemEnemySprite = new Sprite(m_width, GAME_FLOOR, 30, 90, ENEMIES_IMAGE, clipRectTotemEnemy);
    m_totemEnemySprite->setOrigin(0, 150);

    std::vector<sf::IntRect> clipRectBlockEnemy;
    for (int i=0; i<2; i++) clipRectBlockEnemy.push_back(sf::IntRect(50*i, 150, 50, 50));
    m_blockEnemySprite = new Sprite(50, 95, 50, 50, ENEMIES_IMAGE, clipRectBlockEnemy);
    m_blockEnemySprite->setOrigin(0, 50);


    //=== Initialize COINS & BONUSES

    m_shieldImage = new GraphicElement(50, GAME_FLOOR, 40, 40);
    m_shieldImage->setTextureFromImage(SHIELD_IMAGE);
    m_shieldImage->setOrigin(0, 50);

    std::vector<sf::IntRect> clipRect_coin;
    for (int i=0; i<5; i++) clipRect_coin.push_back(sf::IntRect(50*i, 0, 50, 50));
    m_coinSprite = new Sprite(30, 95, 25, 25, BONUS_IMAGE, clipRect_coin);
    m_coinSprite->setOrigin(0, 50);

    std::vector<sf::IntRect> clipRect_pv;
    for (int i=0; i<5; i++)clipRect_pv.push_back(sf::IntRect(50*i, 50, 50, 50));
    m_PVPlusBonusSprite = new Sprite(m_width, GAME_FLOOR, 25, 25, BONUS_IMAGE, clipRect_pv);
    m_PVPlusBonusSprite->setOrigin(0, 50);

    std::vector<sf::IntRect> clipRect_mega;
    for (int i=0; i<5; i++) clipRect_mega.push_back(sf::IntRect(50*i, 100, 50, 50));
    m_megaBonusSprite = new Sprite(100, 50, 25, 25, BONUS_IMAGE, clipRect_mega);
    m_megaBonusSprite->setOrigin(0, 50);

    std::vector<sf::IntRect> clipRect_fly;
    for (int i=0; i<5; i++) clipRect_fly.push_back(sf::IntRect(50*i, 150, 50, 50));
    m_flyBonusSprite = new Sprite(100, 50, 25, 25, BONUS_IMAGE, clipRect_fly);
    m_flyBonusSprite->setOrigin(0, 50);

    std::vector<sf::IntRect> clipRect_slow;
    for (int i=0; i<5; i++) clipRect_slow.push_back(sf::IntRect(50*i, 200, 50, 50));
    m_slowSpeedBonusSprite = new Sprite(100, 50, 25, 25, BONUS_IMAGE, clipRect_slow);
    m_slowSpeedBonusSprite->setOrigin(0, 50);

    std::vector<sf::IntRect> clipRect_shield;
    for (int i=0; i<5; i++) clipRect_shield.push_back(sf::IntRect(50*i, 250, 50, 50));
    m_shieldBonusSprite = new Sprite(100, 50, 25, 25, BONUS_IMAGE, clipRect_shield);
    m_shieldBonusSprite->setOrigin(0, 50);


    //=== Initialize buttons

    std::vector<sf::IntRect> clipRect_resume;
    clipRect_resume.push_back(sf::IntRect(0, 0, 50, 50));
    clipRect_resume.push_back(sf::IntRect(50, 0, 50, 50));
    m_resumeGameButton = new Button(PAUSE_FORM_X, 355, 25, 25, "pause_resume",
                                    GAME_BUTTONS_IMAGE, clipRect_resume);
    m_resumeGameButton->resize(25, 25);
    m_resumeGameButton->setLabelPosition(RIGHT);

    std::vector<sf::IntRect> clipRect_restart;
    clipRect_restart.push_back(sf::IntRect(0, 50, 50, 50));
    clipRect_restart.push_back(sf::IntRect(50, 50, 50, 50));
    m_restartGameButton = new Button(PAUSE_FORM_X, 405, 25, 25, "pause_restart",
                                     GAME_BUTTONS_IMAGE, clipRect_restart);
    m_restartGameButton->resize(25, 25);
    m_restartGameButton->setLabelPosition(RIGHT);


    std::vector<sf::IntRect> clipRect_home;
    clipRect_home.push_back(sf::IntRect(0, 100, 50, 50));
    clipRect_home.push_back(sf::IntRect(50, 100, 50, 50));
    m_goToHomeButton = new Button(PAUSE_FORM_X, 455, 25, 25, "pause_go_to_home",
                                  GAME_BUTTONS_IMAGE, clipRect_home);
    m_goToHomeButton->resize(25, 25);
    m_goToHomeButton->setLabelPosition(RIGHT);

    std::vector<sf::IntRect> clipRect_music;
    clipRect_music.push_back(sf::IntRect(0, 200, 50, 50));
    clipRect_music.push_back(sf::IntRect(50, 200, 50, 50));
    m_controlMusicButton = new Button(PAUSE_FORM_X, 535, 25, 25, "pause_music",
                                      GAME_BUTTONS_IMAGE, clipRect_music);
    m_controlMusicButton->resize(25, 25);
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
 * @date 18/03/16 - 30/01/17
 */
void GameView::linkElements()
{
    for (auto element : m_game->getNewMElementsArray())
    {
        if (element->getType() == PLAYER)
            m_movableElementToSpriteMap[element] = m_playerSprite;
        else if (element->getType() == STANDARD_ENEMY)
            m_movableElementToSpriteMap[element] = new Sprite(*m_stdEnemySprite);
        else if (element->getType() == TOTEM_ENEMY)
            m_movableElementToSpriteMap[element] = new Sprite(*m_totemEnemySprite);
        else if (element->getType() == BLOCK_ENEMY)
            m_movableElementToSpriteMap[element] = new Sprite(*m_blockEnemySprite);
        else if (element->getType() == COIN)
            m_movableElementToSpriteMap[element] = new Sprite(*m_coinSprite);
        else if (element->getType() == PV_PLUS_BONUS)
            m_movableElementToSpriteMap[element] = new Sprite(*m_PVPlusBonusSprite);
        else if (element->getType() == MEGA_BONUS)
            m_movableElementToSpriteMap[element] = new Sprite(*m_megaBonusSprite);
        else if (element->getType() == FLY_BONUS)
            m_movableElementToSpriteMap[element] = new Sprite(*m_flyBonusSprite);
        else if (element->getType() == SLOW_SPEED_BONUS)
            m_movableElementToSpriteMap[element] = new Sprite(*m_slowSpeedBonusSprite);
        else if (element->getType() == SHIELD_BONUS)
            m_movableElementToSpriteMap[element] = new Sprite(*m_shieldBonusSprite);
        //TODO : else throw exception unknown element
    }
    m_game->clearNewMovableElementList();
}


/**
 * Create seamless transition between zones
 * @author Arthur
 * @date 25/04/16 - 02/01/17
 */
void GameView::handleZonesTransition()
{
    if (m_game->getTransitionStatus())
    {
        //Set background speed and position
        m_farTransitionBackground->setPosition(m_farTransitionBackground->getPosition().x - TRANSITION_SPEED, 0);
        m_farScrollingBackground->setScrollingSpeed(TRANSITION_SPEED);
        m_nearScrollingBackground->decreaseAlpha(5);
        if (m_nearScrollingBackground->getAlpha() == 0)
            m_nearScrollingBackground->setScrollingSpeed(0);
        else
            m_nearScrollingBackground->setScrollingSpeed(TRANSITION_SPEED);

        //Update zone background image and position at half transition
        if (m_farTransitionBackground->getPosition().x  <= 5
            && m_farTransitionBackground->getPosition().x  >= -5)
        {
            if (m_game->getCurrentZone() == HILL)
            {
                m_farScrollingBackground->setTextureFromImage(DEFAULT_FAR_PLAIN_BACKGROUND);
                m_nearScrollingBackground->setTextureFromImage(DEFAULT_NEAR_PLAIN_BACKGROUND);
            }
            else
            {
                m_farScrollingBackground->setTextureFromImage(DEFAULT_FAR_HILL_BACKGROUND);
                m_nearScrollingBackground->setTextureFromImage(DEFAULT_NEAR_HILL_BACKGROUND);
            }

            m_farScrollingBackground->setPositions(-300, 0);
            m_nearScrollingBackground->setPositions(0, 0);
        }

        //Update pixel creation of near background from 3/4 transition to end transition
        if (m_farTransitionBackground->getPosition().x < m_width/2 && m_xPixelIntensity >= 0)
        {
            m_xPixelIntensity -= 0.009;
            m_yPixelIntensity -= 0.009;
            m_pixelShader->update(m_xPixelIntensity, m_yPixelIntensity);
        }

        //Finish transition
        if (m_farTransitionBackground->getPosition().x
            + m_farTransitionBackground->getLocalBounds().width <= 0)
        {
            //Update Transition status
            m_game->setTransitionStatus(false);
            m_game->setTransitionPossibleStatus(false);

            //Set current zone
            if (m_game->getCurrentZone() == HILL)
                m_game->setCurrentZone(PLAIN);
            else
                m_game->setCurrentZone(HILL);
        }
    }
    else
    {
        m_farScrollingBackground->setScrollingSpeed((float) (0.5 * m_game->getGameSpeed()));
        m_nearScrollingBackground->setScrollingSpeed(m_game->getGameSpeed());
        m_nearScrollingBackground->increaseAlpha(255);

        if (m_game->getTransitionPossibleStatus()
            && m_farScrollingBackground->getSeparationPositionX() > m_width - 100)
        {
            m_game->setTransitionStatus(true);
            m_xPixelIntensity = 1;
            m_yPixelIntensity = 1;
            m_farTransitionBackground->setPosition(m_farScrollingBackground->getLeftPosition().x + 1200, 0);

            if (m_game->getCurrentZone() == HILL)
            {
                m_pixelShader->load(DEFAULT_NEAR_T1_BACKGROUND);
                m_farTransitionBackground->setTextureFromImage(DEFAULT_FAR_T1_BACKGROUND);
            }
            else
            {
                m_pixelShader->load(DEFAULT_NEAR_T2_BACKGROUND);
                m_farTransitionBackground->setTextureFromImage(DEFAULT_FAR_T2_BACKGROUND);
            }
        }
    }
}


/**
 * Update gElements
 * @author Arthur
 * @date 6/03/16 - 16/04/17
 */
void GameView::updateElements()
{
    if (m_game->getGameState() == RUNNING ||
        m_game->getGameState() == RUNNING_SLOWLY)
    {
        //=== Handle Transitions between zones

        handleZonesTransition();

        //=== Update Game Elements

        m_farScrollingBackground->sync();
        m_nearScrollingBackground->sync();

        m_remainingLifeImage->resize(3*m_game->getPlayer()->getLife(), 50);

        std::map<MovableElement*, Sprite*>::iterator it;
        for(it = m_movableElementToSpriteMap.begin() ; it != m_movableElementToSpriteMap.end() ; ++it)
        {
            m_game->moveMovableElement(it->first);

            float position_x = (it->first)->getPosX();
            float position_y = (it->first)->getPosY();

            it->second->setPosition(position_x, position_y);
            it->second->sync();
            it->second->resize(it->first->getWidth(), it->first->getHeight());
        }

        //=== Update shield sprite

        if (m_game->getPlayer()->getState() == SHIELD)
        {
            m_shieldImage->setPosition(m_game->getPlayer()->getPosX()-5,
                                             m_game->getPlayer()->getPosY()+5);
            m_shieldImage->resize(40, 40);
        }
    }
    else if (m_game->getGameState() == PAUSED)
    {
        if (m_game->getCurrentZone() == HILL)
            m_pauseBackground->setTextureFromImage(PAUSE_HILL_BACKGROUND);
        else
            m_pauseBackground->setTextureFromImage(PAUSE_PLAIN_BACKGROUND);

        m_resumeGameButton->sync(m_game->getDataBase());
        m_restartGameButton->sync(m_game->getDataBase());
        m_restartGameButton->setLabelPosition(RIGHT);
        m_goToHomeButton->sync(m_game->getDataBase());
        m_controlMusicButton->sync(m_game->getDataBase());
        m_coinSprite->sync();
        m_coinSprite->resize(20, 20);
        m_stdEnemySprite->sync();
        m_stdEnemySprite->resize(20, 20);
    }
    else //GAME OVER
    {
        m_goToHomeButton->sync(m_game->getDataBase());
        m_goToHomeButton->resize(30, 30);
        m_goToHomeButton->setPosition(30, 535);

        m_coinSprite->resize(25, 25);
        m_coinSprite->setPosition((float)(m_width / 2.4), 565);

        m_restartGameButton->sync(m_game->getDataBase());
        m_restartGameButton->resize(30, 30);
        m_restartGameButton->setPosition(840, 535);
        m_restartGameButton->setLabelPosition(LEFT);

        m_saveScoreButton->sync(m_game->getDataBase());
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
    std::map<MovableElement *, Sprite *>::iterator it =
            m_movableElementToSpriteMap.begin();
    bool found = false;
    while (!found && it!=m_movableElementToSpriteMap.end())
    {
        if ((it->first)->isColliding())
        {
            if ((it->first)->getType() == COIN)
                m_coinMusic.play();

            if ((it->first)->getType() == STANDARD_ENEMY
                || (it->first)->getType() == TOTEM_ENEMY
                || (it->first)->getType() ==BLOCK_ENEMY)
                m_destructedEnemiesMusic.play();

            delete it->second;
            m_movableElementToSpriteMap.erase(it);
            found = true;
        }
        else
            ++it;
    }
}


/**
 * Synchronization function
 * @author Arthur
 * @date 26/03/16 - 30/01/17
 */
void GameView::synchronize()
{
    switch(m_game->getGameState())
    {
        case RUNNING :
        case RUNNING_SLOWLY :
            linkElements();
            deleteElements();
            updateElements();
            m_textHandler->syncGameText(m_game->getBonusTimeout());
            break;
        case PAUSED:
            updateElements();
            m_textHandler->syncPauseText();
            sf::sleep(sf::milliseconds(140)); //limit CPU usage
            break;
        case OVER:
            if (m_gameThemeMusic.getStatus() == sf::Music::Status::Playing) //Audio ending
                m_gameThemeMusic.stop();
            updateElements();
            m_textHandler->syncEndText((int)m_game->getGameSpeed());
            break;
        default:
            break;
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
    if (m_game->getDataBase()->isGameMusicEnabled())
    {
        std::vector<sf::IntRect> clipRect;
        clipRect.push_back(sf::IntRect(0, 200, 50, 50));
        clipRect.push_back(sf::IntRect(50, 200, 50, 50));
        m_controlMusicButton->setClipRectArray(clipRect);
        m_gameThemeMusic.setVolume(100);
        m_coinMusic.setVolume(100);
        m_destructedEnemiesMusic.setVolume(100);
    }
    else
    {
        std::vector<sf::IntRect> clipRect;
        clipRect.push_back(sf::IntRect(0, 250, 50, 50));
        clipRect.push_back(sf::IntRect(50, 250, 50, 50));
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

    if (m_game->getGameState() == RUNNING ||
        m_game->getGameState() == RUNNING_SLOWLY)
    {
        //=== Standalone GraphicElements drawing

        m_farScrollingBackground->draw(m_window);

        if (m_game->getTransitionStatus())
        {
            m_window->draw(*m_farTransitionBackground);
            if (m_farTransitionBackground->getPosition().x < m_width/2)
                m_window->draw(*m_pixelShader);
        }

        m_nearScrollingBackground->draw(m_window);
        m_window->draw(*m_bottomBarImage);
        m_window->draw(*m_remainingLifeImage);
        m_window->draw(*m_lifeBoxImage);

        //=== Array's GraphicElements drawing

        for(auto it = m_movableElementToSpriteMap.begin() ;
            it != m_movableElementToSpriteMap.end() ; ++it)
        {
            it->second->draw(m_window);
        }

        if (m_game->getPlayer()->getState() == SHIELD)
            m_window->draw(*m_shieldImage);

        //=== TextHandler drawing

        m_textHandler->drawGameText(m_window);
    }
    else if (m_game->getGameState() == PAUSED)
    {
        //=== Background drawing & GraphicElements drawing

        m_window->draw(*m_pauseBackground);
        m_window->draw(*m_distanceIcon);
        m_window->draw(*m_coinSprite);
        m_window->draw(*m_stdEnemySprite);
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

        m_window->draw(*m_endBackground);
        m_window->draw(*m_coinSprite);
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
 * @date 21/02/16 - 30/01/17
 */
bool GameView::treatEvents(sf::Event event)
{
    bool result = false;

    if (m_window->isOpen())
    {
        result = true;

        if (m_game->getGameState() == RUNNING ||
            m_game->getGameState() == RUNNING_SLOWLY)
        {
            //=== Player Controls in Game Screen

            if (KEYBOARD_LEFT)
                m_game->getPlayer()->controlPlayerMovements(MOVE_LEFT);

            else if (KEYBOARD_RIGHT)
                m_game->getPlayer()->controlPlayerMovements(MOVE_RIGHT);

            if (KEYBOARD_JUMP)
                m_game->getPlayer()->setJumpState(true);
        }

        while (m_window->pollEvent(event))
        {
            if  (event.type == sf::Event::Closed)
            {
                m_game->getDataBase()->setAppState(QUIT);
                m_window->close();
                result = false;
            }

            //=== Handle open/quit pause

            if (m_game->getGameState() != OVER && event.type == sf::Event::KeyPressed
                && event.key.code == sf::Keyboard::Escape)
            {
                if (m_game->getGameState() == RUNNING ||
                    m_game->getGameState() == RUNNING_SLOWLY)
                {
                    m_game->setGameState(PAUSED);
                    m_gameThemeMusic.pause();
                }
                else
                {
                    m_game->setGameState(RUNNING_SLOWLY);
                    m_gameThemeMusic.play();
                }
            }

            if (event.type == sf::Event::KeyReleased)
                m_game->getPlayer()->setDecelerationState(true);

            //=== Pause Screen

            if (m_game->getGameState() == PAUSED)
            {
                if (MOUSE_LEFT_PRESSED_EVENT)
                {
                    if (m_resumeGameButton->contains(MOUSE_POSITION))
                        m_resumeGameButton->setPressed(true);

                    else if (m_restartGameButton->contains(MOUSE_POSITION))
                        m_restartGameButton->setPressed(true);

                    else if (m_goToHomeButton->contains(MOUSE_POSITION))
                        m_goToHomeButton->setPressed(true);

                    else if (m_controlMusicButton->contains(MOUSE_POSITION))
                        m_controlMusicButton->setPressed(true);

                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    m_resumeGameButton->setPressed(false);
                    m_restartGameButton->setPressed(false);
                    m_goToHomeButton->setPressed(false);
                    m_controlMusicButton->setPressed(false);

                    if (m_resumeGameButton->contains(MOUSE_POSITION))
                    {
                        m_game->setGameState(RUNNING_SLOWLY);
                        if (m_gameThemeMusic.getStatus() == sf::Music::Status::Paused)
                            m_gameThemeMusic.play();
                    }
                    else if (m_restartGameButton->contains(MOUSE_POSITION))
                    {
                        m_game->getDataBase()->setAppState(RESET_GAME);
                        result = false;
                    }
                    else if (m_goToHomeButton->contains(MOUSE_POSITION))
                    {
                        m_game->getDataBase()->setAppState(MENU);
                        result = false;
                    }
                    else if (m_controlMusicButton->contains(MOUSE_POSITION))
                    {
                        m_game->getDataBase()->setGameMusic(!m_game->getDataBase()->isGameMusicEnabled());
                        handleMusic();
                    }
                }
            }
            else if (m_game->getGameState() == OVER)
            {
                if (MOUSE_LEFT_PRESSED_EVENT)
                {
                    if (m_restartGameButton->contains(MOUSE_POSITION))
                        m_restartGameButton->setPressed(true);

                    else if (m_goToHomeButton->contains(MOUSE_POSITION))
                        m_goToHomeButton->setPressed(true);

                    else if (m_saveScoreButton->contains(MOUSE_POSITION))
                        m_saveScoreButton->setPressed(true);
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    m_restartGameButton->setPressed(false);
                    m_goToHomeButton->setPressed(false);
                    m_saveScoreButton->setPressed(false);

                    if (m_restartGameButton->contains(MOUSE_POSITION))
                    {
                        m_game->getDataBase()->setAppState(RESET_GAME);
                        result = false;
                    }
                    else if (m_goToHomeButton->contains(MOUSE_POSITION))
                    {
                        m_game->getDataBase()->setAppState(MENU);
                        result = false;
                    }
                    else if (m_saveScoreButton->contains(MOUSE_POSITION))
                    {
                        m_saveScoreButton->hide();
                        m_game->getDataBase()->saveCurrentGame();
                    }
                }
            }
        }
    }
    return result;
}
