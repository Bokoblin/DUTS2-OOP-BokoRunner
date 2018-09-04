#include "GameView.h"

using std::string;
using std::vector;
using Bokoblin::SimpleLogger::Logger;

// TODO: SPLIT FILE FOLLOWING GAME STATES (BUT KEEP AS SAME CLASS)

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs the game view
 * with the window, the text manager and its model counterpart
 *
 * @param window the app window
 * @param textManager the text manager
 * @param gameModel the game model counterpart
 *
 * @author Arthur
 * @date 26/03/16 - 29/01/17
 */
GameView::GameView(sf::RenderWindow *window, AppTextManager *textManager, GameModel *gameModel) :
        AbstractView(window, textManager), m_game{gameModel},
        m_xPixelIntensity{1}, m_yPixelIntensity{1}
{
    loadSprites();
    m_pixelShader = new PixelShader();

    //=== change default game music if in master mode

    string game_music = (m_game->getAppCore()->getDifficulty() == EASY)
                        ? GAME_MUSIC_THEME_EASY_MODE
                        : GAME_MUSIC_THEME_HARD_MODE;

    if (!m_gameThemeMusic.openFromFile(game_music))
        Logger::printErrorOnConsole("Music loading failed for \"" + game_music + "\"");
    else
    {
        handleMusic();
        m_gameThemeMusic.play();
        m_gameThemeMusic.setLoop(true);
    }

    //=== change ball skin if not default one

    if (m_game->getAppCore()->getBallSkin() == "morphing")
    {
        vector<sf::IntRect> clipRect;
        for (int i=0; i<8; i++)
            clipRect.emplace_back(50 * i, 50, 50, 50);
        m_playerSprite->setClipRectArray(clipRect);
    }
    else if (m_game->getAppCore()->getBallSkin() == "capsule")
    {
        vector<sf::IntRect> clipRect;
        for (int i=0; i<8; i++)
            clipRect.emplace_back(50 * i, 100, 50, 50);
        m_playerSprite->setClipRectArray(clipRect);
    }

    if (!m_coinMusic.openFromFile(COINS_COLLECTED_MUSIC))
        Logger::printErrorOnConsole("Music loading failed for \"" + COINS_COLLECTED_MUSIC + "\"");

    if (!m_destructedEnemiesMusic.openFromFile(ENEMIES_DESTRUCTED_MUSIC))
        Logger::printErrorOnConsole("Music loading failed for \"" + ENEMIES_DESTRUCTED_MUSIC + "\"");
}


/**
 * Destructor
 * @author Arthur
 * @date 26/03/16 - 24/12/16
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
    delete m_shieldImage;
    delete m_pixelShader;
    for (auto &it : m_typeToSpriteMap)
        delete it.second;
    for (auto &it : m_movableElementToSpriteMap)
        delete it.second;

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


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Loads all sprites used by the game (backgrounds, UI, elements)
 *
 * @author Arthur
 * @date 26/03/16 - 04/02/18
 */
void GameView::loadSprites()
{
    //=== Initialize backgrounds

    m_farScrollingBackground = new ScrollingBackground(1200, m_height, 1, DEFAULT_FAR_HILL_BACKGROUND);
    m_nearScrollingBackground = new ScrollingBackground(1200, m_height, 2, DEFAULT_NEAR_HILL_BACKGROUND);

    m_farTransitionBackground = new mdsf::Sprite(SCREEN_WIDTH, m_height, m_width, m_height, DEFAULT_FAR_T1_BACKGROUND);
    m_bottomBarImage = new mdsf::Sprite(0, 520, 1200, m_height, BOTTOM_BAR_IMAGE);

    m_pauseBackground = new mdsf::Sprite(0, 0, m_width, m_height, PAUSE_HILL_BACKGROUND);
    m_endBackground = new mdsf::Sprite(0, 0, m_width, m_height, END_SCREEN_BACKGROUND);


    //=== Initialize UI elements

    m_lifeBoxImage = new mdsf::Sprite(105, 535, 200, 100);
    m_lifeBoxImage->loadAndApplyTextureFromImageFile(LIFE_BOX_IMAGE, sf::IntRect(0, 0, 300, 50));

    m_remainingLifeImage = new mdsf::Sprite(107, 535, 300, 50);
    m_remainingLifeImage->loadAndApplyTextureFromImageFile(LIFE_BOX_IMAGE, sf::IntRect(0, 51, 300, 50));

    m_distanceIcon = new mdsf::Sprite(30, 35, 25, 25);
    m_distanceIcon->loadAndApplyTextureFromImageFile(GAME_BUTTONS_IMAGE, sf::IntRect(0, 150, 50, 50));
    m_distanceIcon->resize(25, 25);


    //=== Initialize PLAYER sprite

    vector<sf::IntRect> clipRect;
    for (int i=0; i<8; i++) clipRect.emplace_back(50 * i, 0, 50, 50);
    m_playerSprite = new AnimatedSprite(50, GameModel::GAME_FLOOR, 30, 30, BALL_IMAGE, clipRect);
    m_playerSprite->setOrigin(0, 50);


    //=== Initialize ENEMIES sprite

    vector<sf::IntRect> clipRectStdEnemy;
    for (int i=0; i<2; i++) clipRectStdEnemy.emplace_back(50 * i, 0, 50, 50);
    m_stdEnemySprite = new AnimatedSprite(30, 135, 30, 30, ENEMIES_IMAGE, clipRectStdEnemy);
    m_stdEnemySprite->setOrigin(0, 50);

    vector<sf::IntRect> clipRectTotemEnemy;
    for (int i=0; i<2; i++) clipRectTotemEnemy.emplace_back(50 * i, 0, 50, 150);
    m_totemEnemySprite = new AnimatedSprite(m_width, GameModel::GAME_FLOOR, 30, 90, ENEMIES_IMAGE, clipRectTotemEnemy);
    m_totemEnemySprite->setOrigin(0, 150);

    vector<sf::IntRect> clipRectBlockEnemy;
    for (int i=0; i<2; i++) clipRectBlockEnemy.emplace_back(50 * i, 150, 50, 50);
    m_blockEnemySprite = new AnimatedSprite(50, 95, 50, 50, ENEMIES_IMAGE, clipRectBlockEnemy);
    m_blockEnemySprite->setOrigin(0, 50);


    //=== Initialize COINS & BONUSES sprite

    m_shieldImage = new mdsf::Sprite(50, GameModel::GAME_FLOOR, 40, 40);
    m_shieldImage->loadAndApplyTextureFromImageFile(SHIELD_IMAGE);
    m_shieldImage->setOrigin(0, 50);

    vector<sf::IntRect> clipRect_coin;
    for (int i=0; i<5; i++) clipRect_coin.emplace_back(50 * i, 0, 50, 50);
    m_coinSprite = new AnimatedSprite(30, 95, 25, 25, BONUS_IMAGE, clipRect_coin);
    m_coinSprite->setOrigin(0, 50);

    vector<sf::IntRect> clipRect_pv;
    for (int i=0; i<5; i++) clipRect_pv.emplace_back(50 * i, 50, 50, 50);
    m_PVPlusBonusSprite = new AnimatedSprite(m_width, GameModel::GAME_FLOOR, 25, 25, BONUS_IMAGE, clipRect_pv);
    m_PVPlusBonusSprite->setOrigin(0, 50);

    vector<sf::IntRect> clipRect_mega;
    for (int i=0; i<5; i++) clipRect_mega.emplace_back(50*i, 100, 50, 50);
    m_megaBonusSprite = new AnimatedSprite(100, 50, 25, 25, BONUS_IMAGE, clipRect_mega);
    m_megaBonusSprite->setOrigin(0, 50);

    vector<sf::IntRect> clipRect_fly;
    for (int i=0; i<5; i++) clipRect_fly.emplace_back(50 * i, 150, 50, 50);
    m_flyBonusSprite = new AnimatedSprite(100, 50, 25, 25, BONUS_IMAGE, clipRect_fly);
    m_flyBonusSprite->setOrigin(0, 50);

    vector<sf::IntRect> clipRect_slow;
    for (int i=0; i<5; i++) clipRect_slow.emplace_back(50 * i, 200, 50, 50);
    m_slowSpeedBonusSprite = new AnimatedSprite(100, 50, 25, 25, BONUS_IMAGE, clipRect_slow);
    m_slowSpeedBonusSprite->setOrigin(0, 50);

    vector<sf::IntRect> clipRect_shield;
    for (int i=0; i<5; i++) clipRect_shield.emplace_back(50 * i, 250, 50, 50);
    m_shieldBonusSprite = new AnimatedSprite(100, 50, 25, 25, BONUS_IMAGE, clipRect_shield);
    m_shieldBonusSprite->setOrigin(0, 50);


    //=== Initialize buttons

    vector<sf::IntRect> clipRect_resume;
    clipRect_resume.emplace_back(0, 0, 50, 50);
    clipRect_resume.emplace_back(50, 0, 50, 50);
    m_resumeGameButton = new mdsf::Button(PAUSE_FORM_X, 355, 25, 25, "pause_resume",
                                    GAME_BUTTONS_IMAGE, clipRect_resume);
    m_resumeGameButton->resize(PAUSE_BUTTONS_SIZE);
    m_resumeGameButton->setLabelPosition(mdsf::LabelPosition::RIGHT);
    m_resumeGameButton->retrieveAndSyncLabel(LocalizationManager::fetchLocalizedString);

    vector<sf::IntRect> clipRect_restart;
    clipRect_restart.emplace_back(0, 50, 50, 50);
    clipRect_restart.emplace_back(50, 50, 50, 50);
    m_restartGameButton = new mdsf::Button(PAUSE_FORM_X, 405, 25, 25, "pause_restart",
                                     GAME_BUTTONS_IMAGE, clipRect_restart);
    m_restartGameButton->resize(PAUSE_BUTTONS_SIZE);
    m_restartGameButton->setLabelPosition(mdsf::LabelPosition::RIGHT);
    m_restartGameButton->retrieveAndSyncLabel(LocalizationManager::fetchLocalizedString);


    vector<sf::IntRect> clipRect_home;
    clipRect_home.emplace_back(0, 100, 50, 50);
    clipRect_home.emplace_back(50, 100, 50, 50);
    m_goToHomeButton = new mdsf::Button(PAUSE_FORM_X, 455, 25, 25, "pause_go_to_home",
                                  GAME_BUTTONS_IMAGE, clipRect_home);
    m_goToHomeButton->resize(PAUSE_BUTTONS_SIZE);
    m_goToHomeButton->setLabelPosition(mdsf::LabelPosition::RIGHT);
    m_goToHomeButton->retrieveAndSyncLabel(LocalizationManager::fetchLocalizedString);

    vector<sf::IntRect> clipRect_music;
    clipRect_music.emplace_back(0, 200, 50, 50);
    clipRect_music.emplace_back(50, 200, 50, 50);
    m_controlMusicButton = new mdsf::Button(PAUSE_FORM_X, 535, 25, 25, "pause_music",
                                      GAME_BUTTONS_IMAGE, clipRect_music);
    m_controlMusicButton->resize(PAUSE_BUTTONS_SIZE);
    m_controlMusicButton->setLabelPosition(mdsf::LabelPosition::RIGHT);
    m_controlMusicButton->retrieveAndSyncLabel(LocalizationManager::fetchLocalizedString);

    vector<sf::IntRect> clipRect_save;
    clipRect_save.emplace_back(RAISED_BUTTON_DEFAULT);
    clipRect_save.emplace_back(RAISED_BUTTON_PRESSED);
    m_saveScoreButton = new mdsf::Button(m_width / 2 - 75, 350, 150, BUTTON_HEIGHT, "end_save_button",
                                   RECT_BUTTONS_IMAGE, clipRect_save);
    m_saveScoreButton->retrieveAndSyncLabel(LocalizationManager::fetchLocalizedString);
    m_saveScoreButton->setColor(mdsf::Color::MaterialGreenA700);


    //=== Associate element type to sprite

    m_typeToSpriteMap[PLAYER] = m_playerSprite;
    m_typeToSpriteMap[STANDARD_ENEMY] = m_stdEnemySprite;
    m_typeToSpriteMap[TOTEM_ENEMY] = m_totemEnemySprite;
    m_typeToSpriteMap[BLOCK_ENEMY] = m_blockEnemySprite;
    m_typeToSpriteMap[COIN] = m_coinSprite;
    m_typeToSpriteMap[PV_PLUS_BONUS] = m_PVPlusBonusSprite;
    m_typeToSpriteMap[MEGA_BONUS] = m_megaBonusSprite;
    m_typeToSpriteMap[FLY_BONUS] = m_flyBonusSprite;
    m_typeToSpriteMap[SLOW_SPEED_BONUS] = m_slowSpeedBonusSprite;
    m_typeToSpriteMap[SHIELD_BONUS] = m_shieldBonusSprite;
}


/**
 * Links a model movable element to new sprite matching its type
 *
 * @author Arthur
 * @date 18/03/16 - 24/12/17
 */
void GameView::linkElements()
{
    for (auto &element : m_game->getNewMElementsArray())
        m_movableElementToSpriteMap[element] = new AnimatedSprite(*(m_typeToSpriteMap[element->getType()]));

    m_game->clearNewMovableElementList();
}


/**
 * Processes the transition between zones
 *
 * @author Arthur
 * @date 25/04/16 - 26/12/17
 */
void GameView::processZonesTransition()
{
    //=== [Always] Set background speed and position

    m_farTransitionBackground->setPosition(m_farTransitionBackground->getX() - TRANSITION_SPEED, 0);
    m_farScrollingBackground->setScrollingSpeed(TRANSITION_SPEED);
    m_nearScrollingBackground->decreaseAlpha(5);
    if (m_nearScrollingBackground->getAlpha() == 0)
        m_nearScrollingBackground->setScrollingSpeed(0);
    else
        m_nearScrollingBackground->setScrollingSpeed(TRANSITION_SPEED);

    //=== [Transition half only] Update zone background image and position

    if (m_farTransitionBackground->getX()  <= 5
        && m_farTransitionBackground->getX()  >= -5)
    {
        if (m_game->getCurrentZone() == HILL)
        {
            m_farScrollingBackground->loadAndApplyTextureFromImageFile(DEFAULT_FAR_PLAIN_BACKGROUND);
            m_nearScrollingBackground->loadAndApplyTextureFromImageFile(DEFAULT_NEAR_PLAIN_BACKGROUND);
        }
        else
        {
            m_farScrollingBackground->loadAndApplyTextureFromImageFile(DEFAULT_FAR_HILL_BACKGROUND);
            m_nearScrollingBackground->loadAndApplyTextureFromImageFile(DEFAULT_NEAR_HILL_BACKGROUND);
        }

        m_farScrollingBackground->setPositions(-300, 0);
        m_nearScrollingBackground->setPositions(0, 0);
    }

    //=== [Transition 3/4 until end] Update pixel creation of near background

    if (m_farTransitionBackground->getX() < m_width/2 && m_xPixelIntensity >= 0)
    {
        m_xPixelIntensity -= 0.009;
        m_yPixelIntensity -= 0.009;
        m_pixelShader->update(m_xPixelIntensity, m_yPixelIntensity);
    }

    //=== [Transition end]

    if (m_farTransitionBackground->getX()
        + m_farTransitionBackground->getLocalBounds().width <= 0)
    {
        //Update Transition status
        m_game->setTransitionState(false);
        m_game->disableTransitionPossibility();

        //Set current zone and change pause background
        if (m_game->getCurrentZone() == HILL)
        {
            m_game->setCurrentZone(PLAIN);
            m_pauseBackground->loadAndApplyTextureFromImageFile(PAUSE_PLAIN_BACKGROUND);
        }
        else
        {
            m_game->setCurrentZone(HILL);
            m_pauseBackground->loadAndApplyTextureFromImageFile(PAUSE_HILL_BACKGROUND);
        }
    }
}


/**
* Setups the transition between zones
 *
* @author Arthur
* @date 25/04/16 - 26/12/17
*/
void GameView::setupTransition()
{
    m_game->setTransitionState(true);
    m_xPixelIntensity = 1;
    m_yPixelIntensity = 1;
    m_farTransitionBackground->setPosition(m_farScrollingBackground->getLeftPosition().x + 1200, 0);

    if (m_game->getCurrentZone() == HILL)
    {
        m_pixelShader->load(DEFAULT_NEAR_T1_BACKGROUND);
        m_farTransitionBackground->loadAndApplyTextureFromImageFile(DEFAULT_FAR_T1_BACKGROUND);
    }
    else
    {
        m_pixelShader->load(DEFAULT_NEAR_T2_BACKGROUND);
        m_farTransitionBackground->loadAndApplyTextureFromImageFile(DEFAULT_FAR_T2_BACKGROUND);
    }
}


/**
 * Updates elements of a running game
 *
 * @author Arthur
 * @date 6/03/16 - 04/02/18
 */
void GameView::updateRunningGameElements()
{
    //=== Handle Transitions between zones

    if (m_game->isTransitionRunning())
    {
        processZonesTransition();
    }
    else
    {
        m_farScrollingBackground->setScrollingSpeed((float) (0.5 * m_game->getGameSpeed()));
        m_nearScrollingBackground->setScrollingSpeed(m_game->getGameSpeed());
        m_nearScrollingBackground->setAlpha(255);

        if (m_game->isTransitionPossible()
            && m_farScrollingBackground->getSeparationPositionX(m_width) > m_width - 100)
            setupTransition();
    }

    //=== Update Game Elements

    m_farScrollingBackground->sync();
    m_nearScrollingBackground->sync();

    m_remainingLifeImage->resize(3*m_game->getPlayer()->getLife(), 50);

    for(auto &it : m_movableElementToSpriteMap)
    {
        m_game->moveMovableElement(it.first);

        float position_x = (it.first)->getPosX();
        float position_y = (it.first)->getPosY();

        it.second->setPosition(position_x, position_y);
        it.second->sync();
        it.second->resize(it.first->getWidth(), it.first->getHeight());
    }

    //=== Update shield sprite

    if (m_game->getPlayer()->getState() == SHIELDED || m_game->getPlayer()->getState() == HARD_SHIELDED)
    {
        if (m_game->getPlayer()->getState() == SHIELDED)
            m_shieldImage->setTextureRect(sf::IntRect(0, 0, 50, 50));
        else
            m_shieldImage->setTextureRect(sf::IntRect(50, 0, 50, 50));

        m_shieldImage->setPosition(m_game->getPlayer()->getPosX()-5,
                                   m_game->getPlayer()->getPosY()+5);
        m_shieldImage->resize(40, 40);
    }
}


/**
 * Updates elements of a paused game
 *
 * @author Arthur
 * @date 6/03/16 - 26/12/17
 */
void GameView::updatePausedGameElements()
{
    m_resumeGameButton->sync();
    m_restartGameButton->sync();
    m_goToHomeButton->sync();
    m_controlMusicButton->sync();
    m_coinSprite->sync();
    m_coinSprite->resize(20, 20);
    m_stdEnemySprite->sync();
    m_stdEnemySprite->resize(20, 20);
}


/**
 * Updates elements of a game over
 *
 * @author Arthur
 * @date 6/03/16 - 24/12/17
 */
void GameView::updateGameOverElements()
{
    m_goToHomeButton->sync();
    m_goToHomeButton->resize(30, 30);
    m_goToHomeButton->setPosition(30, 535);
    m_goToHomeButton->syncLabelPosition();

    m_coinSprite->sync();
    m_coinSprite->resize(25, 25);
    m_coinSprite->setPosition((float)(m_width / 2.3), 563);

    m_restartGameButton->sync();
    m_restartGameButton->resize(30, 30);
    m_restartGameButton->setPosition(840, 535);
    m_restartGameButton->setLabelPosition(mdsf::LabelPosition::LEFT);
    m_restartGameButton->syncLabelPosition();

    m_saveScoreButton->sync();
    m_saveScoreButton->setPositionSelfCentered(m_width/2, 430);
    m_saveScoreButton->syncLabelPosition();
}


/**
 * Deletes the Sprite that collided with the player
 * We consider that the player only collide with one element per complete loop,
 * it allows to reduce average complexity instead doing n loops each time (worst case)
 *
 * @author Arthur
 * @date 12/03/16 - 20/03/16
 */
void GameView::deleteElements()
{
    auto it = m_movableElementToSpriteMap.begin();
    bool found = false;

    while (!found && it!=m_movableElementToSpriteMap.end())
    {
        if ((it->first)->isColliding())
        {
            if ((it->first)->getType() == COIN)
                m_coinMusic.play();

            if ((it->first)->getType() == STANDARD_ENEMY
                || (it->first)->getType() == TOTEM_ENEMY
                || (it->first)->getType() == BLOCK_ENEMY)
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
 * Synchronizes game elements
 *
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
            updateRunningGameElements();
            m_textManager->syncGameRunningText(m_game->getBonusTimeout());
            break;
        case PAUSED:
            updatePausedGameElements();
            m_textManager->syncGamePausedText();
            sf::sleep(sf::milliseconds(140)); //limit CPU usage for this thread
            break;
        case OVER:
            //Stop game music if still playing
            if (m_gameThemeMusic.getStatus() == sf::Music::Status::Playing)
                m_gameThemeMusic.stop();
            updateGameOverElements();
            m_textManager->syncGameOverText((int) m_game->getGameSpeed());
            break;
        default:
            break;
    }
}


/**
 * Draws elements of a running game
 *
 * @author Arthur
 * @date 24/12/17
 */
void GameView::drawRunningGame() const
{
    //=== Standalone Sprites drawing

    m_farScrollingBackground->draw(m_window);

    if (m_game->isTransitionRunning())
    {
        m_window->draw(*m_farTransitionBackground);
        if (m_farTransitionBackground->getX() < m_width/2)
            m_window->draw(*m_pixelShader);
    }

    m_nearScrollingBackground->draw(m_window);
    m_window->draw(*m_bottomBarImage);
    m_window->draw(*m_remainingLifeImage);
    m_window->draw(*m_lifeBoxImage);

    //=== Array's Sprites drawing

    for (const auto &it : m_movableElementToSpriteMap)
        it.second->draw(m_window);

    if (m_game->getPlayer()->getState() == SHIELDED || m_game->getPlayer()->getState() == HARD_SHIELDED)
        m_window->draw(*m_shieldImage);

    //=== Standalone Text drawing

    m_textManager->drawGameRunningText(m_window);
}


/**
 * Draws elements of a paused game
 *
 * @author Arthur
 * @date 24/12/17
 */
void GameView::drawPausedGame() const
{
    //=== Background drawing & Sprites drawing

    m_window->draw(*m_pauseBackground);
    m_window->draw(*m_distanceIcon);
    m_window->draw(*m_coinSprite);
    m_window->draw(*m_stdEnemySprite);

    m_resumeGameButton->draw(m_window);
    m_restartGameButton->draw(m_window);
    m_goToHomeButton->draw(m_window);
    m_controlMusicButton->draw(m_window);

    //=== Standalone Text drawing

    m_textManager->drawGamePausedText(m_window);
}


/**
 * Draws elements of a game over
 *
 * @author Arthur
 * @date 24/12/17
 */
void GameView::drawGameOver() const
{
    //=== Background drawing & Buttons drawing

    m_window->draw(*m_endBackground);
    m_window->draw(*m_coinSprite);

    m_restartGameButton->draw(m_window);
    m_goToHomeButton->draw(m_window);
    m_saveScoreButton->draw(m_window);

    //=== Standalone Text drawing

    m_textManager->drawGameOverText(m_window);
}


/**
 * Draws game elements on the window
 *
 * @author Arthur
 * @date 26/03/16 - 24/12/17
 */
void GameView::draw() const
{
    m_window->clear();

    switch(m_game->getGameState())
    {
        case RUNNING :
        case RUNNING_SLOWLY :
            drawRunningGame();
            break;
        case PAUSED:
            drawPausedGame();
            break;
        case OVER:
            drawGameOver();
            break;
        default:
            break;
    }

    m_window->display();
}


/**
 * Handles music settings
 *
 * @author Arthur
 * @date 25/01/17
 */
void GameView::handleMusic()
{
    //change music volume
    if (m_game->getAppCore()->isGameMusicEnabled())
    {
        vector<sf::IntRect> clipRect;
        clipRect.emplace_back(0, 200, 50, 50);
        clipRect.emplace_back(50, 200, 50, 50);
        m_controlMusicButton->setClipRectArray(clipRect);
        m_gameThemeMusic.setVolume(100);
        m_coinMusic.setVolume(100);
        m_destructedEnemiesMusic.setVolume(100);
    }
    else
    {
        vector<sf::IntRect> clipRect;
        clipRect.emplace_back(0, 250, 50, 50);
        clipRect.emplace_back(50, 250, 50, 50);
        m_controlMusicButton->setClipRectArray(clipRect);
        m_gameThemeMusic.setVolume(0);
        m_coinMusic.setVolume(0);
        m_destructedEnemiesMusic.setVolume(0);
    }
}


/**
 * Handle players inputs
 *
 * @author Arthur
 * @date 26/12/17
 */
void GameView::handlePlayerInput() const
{
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
}


/**
 * Handle running game events
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 26/12/17 - 26/01/18
 */
bool GameView::handleRunningGameEvents(sf::Event event)
{
    if (event.type == sf::Event::KeyReleased)
        m_game->getPlayer()->setDecelerationState(true);
    return true;
}


/**
 * Handle paused game events
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 26/12/17 - 04/02/18
 */
bool GameView::handlePausedGameEvents(sf::Event event)
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
            return false;
        }
        else if (m_goToHomeButton->contains(MOUSE_POSITION))
        {
            m_game->getAppCore()->setAppState(MENU);
            return false;
        }
        else if (m_controlMusicButton->contains(MOUSE_POSITION))
        {
            m_game->getAppCore()->toggleGameMusic();
            handleMusic();
        }
    }
    return true;
}


/**
 * Handle game over events
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 26/12/17
 */
bool GameView::handleGameOverEvents(sf::Event event)
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
            return false;
        }
        else if (m_goToHomeButton->contains(MOUSE_POSITION))
        {
            m_game->getAppCore()->setAppState(MENU);
            return false;
        }
        else if (m_saveScoreButton->contains(MOUSE_POSITION))
        {
            m_saveScoreButton->hide();
            m_game->getAppCore()->saveCurrentGame();
            PersistenceManager::updatePersistence();
        }
    }
    return true;
}


/**
 * Handles the user interaction events (mouse, keyboard, title bar buttons)
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur, Florian
 * @date 21/02/16 - 26/12/17
 */
bool GameView::handleEvents(sf::Event event)
{
    handlePlayerInput();

    while (m_window->pollEvent(event))
    {
        //=== Window event handling

        if (event.type == sf::Event::Closed)
        {
            m_game->getAppCore()->setAppState(QUIT);
            return false;
        }

        //=== Pause opening/quitting handling

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            switch(m_game->getGameState())
            {
                case RUNNING :
                case RUNNING_SLOWLY :
                    m_game->setGameState(PAUSED);
                    m_gameThemeMusic.pause();
                    break;
                case PAUSED:
                    m_game->setGameState(RUNNING_SLOWLY);
                    m_gameThemeMusic.play();
                    break;
                default:
                    break;
            }
        }

        //=== Specific game state handling

        switch(m_game->getGameState())
        {
            case RUNNING :
            case RUNNING_SLOWLY :
                return handleRunningGameEvents(event);
            case PAUSED:
                return handlePausedGameEvents(event);
            case OVER:
                return handleGameOverEvents(event);
            default:
                break;
        }
    }
    return true;
}
