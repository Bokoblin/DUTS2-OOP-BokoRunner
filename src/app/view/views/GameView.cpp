#include "GameView.h"

using std::string;
using std::vector;
using Bokoblin::SimpleLogger::Logger;
namespace ViewResources = Bokoblin::BokoRunner::Resources::View;

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * @brief Constructor
 *
 * @param window the app window
 * @param textManager the text manager
 * @param gameModel the game model counterpart
 *
 * @author Arthur
 * @date 26/03/2016 - 11/09/2018
 */
GameView::GameView(sf::RenderWindow* window, AppTextManager* textManager, GameModel* gameModel) :
        AbstractView(window, textManager), m_game{gameModel},
        m_xPixelIntensity{INITIAL_PIXEL_INTENSITY}, m_yPixelIntensity{INITIAL_PIXEL_INTENSITY}
{
    loadSprites();
    m_pixelShader = new PixelShader();

    //=== change default game music if in master mode

    string game_music = (m_game->getGameDifficulty() == EASY)
            ? ViewResources::GAME_MUSIC_THEME_EASY_MODE
            : ViewResources::GAME_MUSIC_THEME_HARD_MODE;

    if (!m_gameThemeMusic.openFromFile(game_music)) {
        Logger::printError("Music loading failed for \"" + game_music + "\"");
    } else {
        handleMusic();
        m_gameThemeMusic.play();
        m_gameThemeMusic.setLoop(true);
    }

    //=== change ball skin if not default one

    if (m_game->getPlayerSkin() == "morphing") {
        vector<sf::IntRect> clipRect;
        for (int i = 0; i < NB_PLAYER_CLIPS; i++) {
            clipRect.emplace_back(50 * i, 50, 50, 50);
        }
        m_playerSprite->setClipRectArray(clipRect);
    } else if (m_game->getPlayerSkin() == "capsule") {
        vector<sf::IntRect> clipRect;
        for (int i = 0; i < NB_PLAYER_CLIPS; i++) {
            clipRect.emplace_back(50 * i, 100, 50, 50);
        }
        m_playerSprite->setClipRectArray(clipRect);
    }

    if (!m_coinMusic.openFromFile(ViewResources::COINS_COLLECTED_MUSIC)) {
        Logger::printError("Music loading failed for \"" + ViewResources::COINS_COLLECTED_MUSIC + "\"");
    }

    if (!m_destructedEnemiesMusic.openFromFile(ViewResources::ENEMIES_DESTRUCTED_MUSIC)) {
        Logger::printError("Music loading failed for \"" + ViewResources::ENEMIES_DESTRUCTED_MUSIC + "\"");
    }
}

/**
 * @brief Destructor
 *
 * @author Arthur
 * @date 26/03/2016 - 13/07/2019
 */
GameView::~GameView()
{
    //=== Delete Game Element

    delete m_parallaxBackground;
    delete m_farTransitionBackground;
    delete m_bottomBarImage;
    delete m_lifeBoxImage;
    delete m_remainingLifeImage;
    delete m_shieldImage;
    delete m_pixelShader;
    for (auto& it : m_typeToSpriteMap) {
        delete it.second;
    }
    for (auto& it : m_movableElementToSpriteMap) {
        delete it.second;
    }

    //=== Delete Pause and End Elements

    delete m_pauseBackground;
    delete m_distanceIcon;
    delete m_endBackground;
    delete m_resumeGameButton;
    delete m_restartGameButton;
    delete m_goToHomeButton;
    delete m_controlMusicButton;
    delete m_saveScoreButton;

    //=== Remove game reference

    m_game = nullptr; //Model memory mustn't be freed by the view
}

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Load all sprites used by the game (backgrounds, UI, elements)
 *
 * @author Arthur
 * @date 26/03/2016 - 13/07/2019
 */
void GameView::loadSprites()
{
    //=== Initialize backgrounds

    m_parallaxBackground = new ParallaxBackground(1.33f * m_width, m_height);
    m_parallaxBackground->addBackground(SCROLLING_BACKGROUND, 1, ViewResources::GAME_FAR_HILL_BACKGROUND);
    m_parallaxBackground->addBackground(SCROLLING_FOREGROUND, 2, ViewResources::GAME_NEAR_HILL_BACKGROUND);

    m_farTransitionBackground = new mdsf::Sprite(m_width, m_height, m_width, m_height, ViewResources::GAME_FAR_T1_BACKGROUND);
    m_bottomBarImage = new mdsf::Sprite(0, 0.87f * m_height, m_width, m_height, ViewResources::BOTTOM_BAR_IMAGE);
    m_bottomBarImage->resize(m_width, m_height);

    m_pauseBackground = new mdsf::Sprite(0, 0, m_width, m_height, ViewResources::PAUSE_HILL_BACKGROUND);
    m_pauseBackground->resize(m_width, m_height);
    m_endBackground = new mdsf::Sprite(0, 0, m_width, m_height, ViewResources::END_SCREEN_BACKGROUND);
    m_endBackground->resize(m_width, m_height);


    //=== Initialize UI elements

    m_lifeBoxImage = new mdsf::Sprite(0.117f * m_width, 0.89f * m_height, LIFE_BOX_WIDTH, LIFE_BOX_HEIGHT);
    m_lifeBoxImage->loadAndApplyTextureFromImageFile(ViewResources::LIFE_BOX_IMAGE, sf::IntRect(0, 0, 300, 50));

    m_remainingLifeImage = new mdsf::Sprite(0.118f * m_width, 0.89f * m_height, LIFE_LEVEL_WIDTH, LIFE_LEVEL_HEIGHT);
    m_remainingLifeImage->loadAndApplyTextureFromImageFile(ViewResources::LIFE_BOX_IMAGE, sf::IntRect(0, 51, 300, 50));

    m_distanceIcon = new mdsf::Sprite(0.033f * m_width, 0.055f * m_height, ORIGINAL_DISTANCE_ICON_SIZE);
    m_distanceIcon->loadAndApplyTextureFromImageFile(ViewResources::GAME_BUTTONS_IMAGE, sf::IntRect(0, 150, 50, 50));
    m_distanceIcon->resize(PAUSE_ICONS_SIZE); //TODO [2.0.x] Move resize call to ctor/sync() after setting the target size in ctor


    //=== Initialize PLAYER sprite

    vector<sf::IntRect> clipRect;
    for (int i = 0; i < 8; i++) clipRect.emplace_back(50 * i, 0, 50, 50);
    m_playerSprite = new AnimatedSprite(-1, -1, 30, 30, ViewResources::BALL_IMAGE, clipRect);
    m_playerSprite->setOrigin(0, 50);


    //=== Initialize ENEMIES sprite

    vector<sf::IntRect> clipRectStdEnemy;
    for (int i = 0; i < 2; i++) clipRectStdEnemy.emplace_back(50 * i, 0, 50, 50);
    m_stdEnemySprite = new AnimatedSprite(-1, -1, 30, 30, ViewResources::ENEMIES_IMAGE, clipRectStdEnemy);
    m_stdEnemySprite->setOrigin(0, 50);

    vector<sf::IntRect> clipRectTotemEnemy;
    for (int i = 0; i < 2; i++) clipRectTotemEnemy.emplace_back(50 * i, 0, 50, 150);
    m_totemEnemySprite = new AnimatedSprite(-1, -1, 30, 90, ViewResources::ENEMIES_IMAGE, clipRectTotemEnemy);
    m_totemEnemySprite->setOrigin(0, 150);

    vector<sf::IntRect> clipRectBlockEnemy;
    for (int i = 0; i < 2; i++) clipRectBlockEnemy.emplace_back(50 * i, 150, 50, 50);
    m_blockEnemySprite = new AnimatedSprite(-1, -1, 50, 50, ViewResources::ENEMIES_IMAGE, clipRectBlockEnemy);
    m_blockEnemySprite->setOrigin(0, 50);


    //=== Initialize COINS & BONUSES sprite

    m_shieldImage = new mdsf::Sprite(-1, -1, SHIELD_SIZE);
    m_shieldImage->loadAndApplyTextureFromImageFile(ViewResources::SHIELD_IMAGE);
    m_shieldImage->setOrigin(0, 50);

    vector<sf::IntRect> clipRect_coin;
    for (int i = 0; i < 5; i++) clipRect_coin.emplace_back(50 * i, 0, 50, 50);
    m_coinSprite = new AnimatedSprite(-1, -1, 25, 25, ViewResources::BONUS_IMAGE, clipRect_coin);
    m_coinSprite->setOrigin(0, 50);

    vector<sf::IntRect> clipRect_pv;
    for (int i = 0; i < 5; i++) clipRect_pv.emplace_back(50 * i, 50, 50, 50);
    m_PVPlusBonusSprite = new AnimatedSprite(-1, -1, 25, 25, ViewResources::BONUS_IMAGE, clipRect_pv);
    m_PVPlusBonusSprite->setOrigin(0, 50);

    vector<sf::IntRect> clipRect_mega;
    for (int i = 0; i < 5; i++) clipRect_mega.emplace_back(50 * i, 100, 50, 50);
    m_megaBonusSprite = new AnimatedSprite(-1, -1, 25, 25, ViewResources::BONUS_IMAGE, clipRect_mega);
    m_megaBonusSprite->setOrigin(0, 50);

    vector<sf::IntRect> clipRect_fly;
    for (int i = 0; i < 5; i++) clipRect_fly.emplace_back(50 * i, 150, 50, 50);
    m_flyBonusSprite = new AnimatedSprite(-1, -1, 25, 25, ViewResources::BONUS_IMAGE, clipRect_fly);
    m_flyBonusSprite->setOrigin(0, 50);

    vector<sf::IntRect> clipRect_slow;
    for (int i = 0; i < 5; i++) clipRect_slow.emplace_back(50 * i, 200, 50, 50);
    m_slowSpeedBonusSprite = new AnimatedSprite(-1, -1, 25, 25, ViewResources::BONUS_IMAGE, clipRect_slow);
    m_slowSpeedBonusSprite->setOrigin(0, 50);

    vector<sf::IntRect> clipRect_shield;
    for (int i = 0; i < 5; i++) clipRect_shield.emplace_back(50 * i, 250, 50, 50);
    m_shieldBonusSprite = new AnimatedSprite(-1, -1, 25, 25, ViewResources::BONUS_IMAGE, clipRect_shield);
    m_shieldBonusSprite->setOrigin(0, 50);


    //=== Initialize buttons

    vector<sf::IntRect> clipRect_resume;
    clipRect_resume.emplace_back(0, 0, 50, 50);
    clipRect_resume.emplace_back(50, 0, 50, 50);
    //TODO [MDC-CPP] Convert to raised button
    m_resumeGameButton = new mdsf::Button(PAUSE_FORM_X, 0.592f * m_height, PAUSE_ICONS_SIZE, PAUSE_ICONS_SIZE,
                                          "pause_resume", ViewResources::GAME_BUTTONS_IMAGE, clipRect_resume);
    m_resumeGameButton->resize(PAUSE_BUTTONS_SIZE);
    m_resumeGameButton->setLabelPosition(mdsf::LabelPosition::RIGHT);
    m_resumeGameButton->retrieveLabel(LocalizationManager::fetchLocalizedString);

    vector<sf::IntRect> clipRect_restart;
    clipRect_restart.emplace_back(0, 50, 50, 50);
    clipRect_restart.emplace_back(50, 50, 50, 50);
    m_restartGameButton = new mdsf::Button(PAUSE_FORM_X, 0.675f * m_height, PAUSE_ICONS_SIZE, PAUSE_ICONS_SIZE,
                                           "pause_restart", ViewResources::GAME_BUTTONS_IMAGE, clipRect_restart);
    m_restartGameButton->resize(PAUSE_BUTTONS_SIZE);
    m_restartGameButton->setLabelPosition(mdsf::LabelPosition::RIGHT);
    m_restartGameButton->retrieveLabel(LocalizationManager::fetchLocalizedString);

    vector<sf::IntRect> clipRect_home;
    clipRect_home.emplace_back(0, 100, 50, 50);
    clipRect_home.emplace_back(50, 100, 50, 50);
    m_goToHomeButton = new mdsf::Button(PAUSE_FORM_X, 0.758f * m_height, PAUSE_ICONS_SIZE, PAUSE_ICONS_SIZE,
                                        "pause_go_to_home", ViewResources::GAME_BUTTONS_IMAGE, clipRect_home);
    m_goToHomeButton->resize(PAUSE_BUTTONS_SIZE);
    m_goToHomeButton->setLabelPosition(mdsf::LabelPosition::RIGHT);
    m_goToHomeButton->retrieveLabel(LocalizationManager::fetchLocalizedString);

    vector<sf::IntRect> clipRect_music;
    clipRect_music.emplace_back(0, 200, 50, 50);
    clipRect_music.emplace_back(50, 200, 50, 50);
    m_controlMusicButton = new mdsf::Button(PAUSE_FORM_X, 0.89f * m_height, PAUSE_ICONS_SIZE, PAUSE_ICONS_SIZE,
                                            "pause_music", ViewResources::GAME_BUTTONS_IMAGE, clipRect_music);
    m_controlMusicButton->resize(PAUSE_BUTTONS_SIZE);
    m_controlMusicButton->setLabelPosition(mdsf::LabelPosition::RIGHT);
    m_controlMusicButton->retrieveLabel(LocalizationManager::fetchLocalizedString);

    m_saveScoreButton = new mdsf::RaisedButton(getHalfXPosition() - (0.5f * BUTTON_WIDTH), 0.72f * m_height,
                                               BUTTON_WIDTH, BUTTON_HEIGHT, "end_save_button");
    m_saveScoreButton->retrieveLabel(LocalizationManager::fetchLocalizedString);
    m_saveScoreButton->setFillColor(mdsf::Color::MaterialGreenA700);


    //=== Associate element type to sprite

    //FIXME [2.0.x] Use AnimatedSprite Ctor with no posX and PosY above as useless
    //FIXME [2.0.x] Replace unneeded members above by function variables
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
 * @brief Synchronize game elements
 *
 * @author Arthur
 * @date 26/03/2016 - 30/01/2017
 */
void GameView::synchronize()
{
    switch (m_game->getGameState()) {
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
            if (m_gameThemeMusic.getStatus() == sf::Music::Status::Playing) {
                m_gameThemeMusic.stop();
            }
            updateGameOverElements();
            m_textManager->syncGameOverText(static_cast<int>(m_game->getGameSpeed()));
            break;
        default:
            break;
    }
}


/**
 * @brief Draw game elements on the window
 *
 * @author Arthur
 * @date 26/03/2016 - 24/12/2017
 */
void GameView::draw() const
{
    m_window->clear();

    switch (m_game->getGameState()) {
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
 * @brief Handle music settings
 *
 * @author Arthur
 * @date 25/01/2017
 */
void GameView::handleMusic()
{
    //change music volume
    if (m_game->isMusicEnabled()) {
        vector<sf::IntRect> clipRect;
        clipRect.emplace_back(0, 200, 50, 50);
        clipRect.emplace_back(50, 200, 50, 50);
        m_controlMusicButton->setClipRectArray(clipRect);
        m_gameThemeMusic.setVolume(100);
        m_coinMusic.setVolume(100);
        m_destructedEnemiesMusic.setVolume(100);
    } else {
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
 * @brief Handle players inputs
 *
 * @author Arthur
 * @date 26/12/2017 - 30/10/2018
 */
void GameView::handlePlayerInput() const
{
    if (m_game->getGameState() == RUNNING ||
            m_game->getGameState() == RUNNING_SLOWLY) {
        //=== Player Controls in Game Screen

        if (EventUtils::wasKeyboardLeftPressed()) {
            m_game->getPlayer()->controlPlayerMovements(MOVE_LEFT);
        } else if (EventUtils::wasKeyboardRightPressed()) {
            m_game->getPlayer()->controlPlayerMovements(MOVE_RIGHT);
        }

        if (EventUtils::wasKeyboardJumpPressed()) {
            m_game->getPlayer()->jump();
        }
    }
}

/**
 * @brief Handle the user interaction events (mouse, keyboard, title bar buttons)
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur, Florian
 * @date 21/02/2016 - 13/01/2019
 */
bool GameView::handleEvents(sf::Event& event)
{
    handlePlayerInput();

    while (m_window->pollEvent(event)) {
        //=== Window event handling

        if (event.type == sf::Event::Closed) {
            m_game->setAppState(QUIT);
            return false;
        }

        //=== Pause opening/quitting handling

        if (EventUtils::wasKeyboardEscapePressed(event)) {
            switch (m_game->getGameState()) {
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

        switch (m_game->getGameState()) {
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
