#include <app/model/utils/GameUtils.h>
#include "GameModel.h"

using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::string;
using Bokoblin::SimpleLogger::Logger;

//------------------------------------------------
//          CONSTRUCTOR / DESTRUCTOR
//------------------------------------------------

/**
 * @brief Constructor
 *
 * @param width the app's width
 * @param height the app's height
 * @param appCore the app's core singleton
 *
 * @author Arthur
 * @date 26/03/2016 - 05/09/2018
 */
GameModel::GameModel(float width, float height, AppCore* appCore) :
        AbstractModel(appCore), m_width{width}, m_height{height}, m_gameState{RUNNING}, m_inTransition{false},
        m_isTransitionPossible{false}, m_gameSlowSpeed{0}, m_currentZone{HILL},
        m_currentEnemySpawnDistance{0}, m_currentCoinSpawnDistance{0}, m_currentBonusSpawnDistance{0},
        m_scoreBonusFlattenedEnemies{0}, m_lastTime{system_clock::now()}, m_bonusTimeout{0}
{
    //=== Initialize new game

    PersistenceManager::fetchActivatedBonus();
    m_appCore->launchNewGame();
    m_gameSpeed = m_appCore->getDifficulty() * DEFAULT_SPEED;
    addANewMovableElement(DEFAULT_PLAYER_X, getGameFloorPosition(), PLAYER);


    //=== Initialize elements spawn distance

    m_nextCoinSpawnDistance = RandomUtils::getUniformRandomNumber(0, 10);       //Between 0 and 10 meters
    m_nextEnemySpawnDistance = RandomUtils::getUniformRandomNumber(10, 20);     //Between 10 and 20 meters
    m_nextBonusSpawnDistance = RandomUtils::getUniformRandomNumber(100, 150);   //Between 100 and 150 meters
}

/**
 * @brief Destructor
 *
 * @author Arthur
 * @date 26/03/2016 - 24/12/2017
 */
GameModel::~GameModel()
{
    for (auto& element : m_movableElementsArray) {
        delete element;
    }

    m_movableElementsArray.clear();
}

//------------------------------------------------
//          GETTERS
//------------------------------------------------

GameState GameModel::getGameState() const { return m_gameState; }
int GameModel::getGameDifficulty() const { return m_appCore->getDifficulty(); }
const string GameModel::getPlayerSkin() const { return m_appCore->getBallSkin(); }
float GameModel::getGameSpeed() const { return m_gameSpeed; }
int GameModel::getBonusTimeout() const { return static_cast<int>(m_bonusTimeout.count() / 1000); } // return seconds
Zone GameModel::getCurrentZone() const { return m_currentZone; }
Player* GameModel::getPlayer() const { return m_player; }
const std::set<MovableElement*>& GameModel::getNewMElementsArray() const { return m_newMovableElementsArray; }
unsigned int GameModel::getGameFloorPosition() const { return static_cast<unsigned int>(0.8f * m_height); }
bool GameModel::isTransitionRunning() const { return m_inTransition; }
bool GameModel::isTransitionPossible() const { return m_isTransitionPossible; }
bool GameModel::isMusicEnabled() const { return m_appCore->isGameMusicEnabled(); }

//------------------------------------------------
//          SETTERS
//------------------------------------------------

void GameModel::setGameState(const GameState& state) { m_gameState = state; }
void GameModel::setCurrentZone(const Zone& z) { m_currentZone = z; }
void GameModel::setTransitionState(bool inTransition) { m_inTransition = inTransition; }
void GameModel::disableTransitionPossibility() { m_isTransitionPossible = false; }
void GameModel::toggleGameMusic() { m_appCore->toggleGameMusic(); }

//------------------------------------------------
//          PUBLIC METHODS
//------------------------------------------------

/**
 * @brief Handle game mode changing and game's evolution
 * (elements apparition, behaviours, deletion)
 *
 * @author Arthur
 * @date 21/02/2016 - 22/03/2020
 */
void GameModel::nextStep()
{
    if (m_gameState == RUNNING || m_gameState == RUNNING_SLOWLY) {
        handleMovableElementsCollisions();

        system_clock::duration currentNextStepDelay = system_clock::now() - m_lastTime;
        system_clock::duration nextStepDelay = milliseconds(NEXT_STEP_DELAY);

        if (currentNextStepDelay.count() > nextStepDelay.count()) {
            handleSpeedAndDistance();
            handleMovableElementsCreation();
            handleMovableElementsDeletion();
            handleBonusTimeout();

            conditionallyAllowZoneTransition();
            conditionallyTriggerGameOver();

            m_lastTime = system_clock::now();
        }
    }
}

/**
 * @brief Save current game progress
 *
 * @author Arthur
 * @date 30/10/18
 */
void GameModel::saveCurrentGame()
{
    m_appCore->saveCurrentGame();
}

/**
 * @brief Allow all elements to trigger their move function
 *
 * @param currentElement the element to move
 *
 * @author Arthur
 * @date 06/03/16 - 26/03/16
 */
void GameModel::moveMovableElement(MovableElement* currentElement)
{
    if (currentElement == m_player) {
        currentElement->move();
    } else if (currentElement != nullptr) {
        repeat(this->m_gameSpeed) {
            currentElement->move();
        }
    }
}

/**
 * @brief Clean the list of new movable elements
 *
 * @author Arthur, Florian
 * @date 02/03/16
 */
void GameModel::clearNewMovableElementList()
{
    m_newMovableElementsArray.clear();
}

//------------------------------------------------
//          PRIVATE METHODS
//------------------------------------------------

/**
 * @brief Handle speed and distance increase
 *
 * @author Arthur
 * @date 04/02/18 - 05/09/18
 */
void GameModel::handleSpeedAndDistance()
{
    if (m_gameSpeed < SPEED_LIMIT && m_gameState != RUNNING_SLOWLY) {
        m_gameSpeed += SPEED_STEP;
    }

    m_appCore->increaseCurrentDistance(m_gameSpeed / SPEED_DISTANCE_RATIO);
}

/**
 * @brief Handle elements creation
 *
 * @author Arthur
 * @date 12/04/16 - 06/09/18
 */
void GameModel::handleMovableElementsCreation()
{
    if (!m_isTransitionPossible && checkIfPositionFree(m_width, getGameFloorPosition())) {
        //=== Add new enemies

        if (m_currentEnemySpawnDistance >= m_nextEnemySpawnDistance) {
            float pos_x = m_width;
            float pos_y = getGameFloorPosition();
            addANewMovableElement(pos_x, pos_y, STANDARD_ENEMY);

            m_currentEnemySpawnDistance = 0;
            m_nextEnemySpawnDistance = GameUtils::chooseSpawnDistance(m_nextEnemySpawnDistance, STANDARD_ENEMY);
            if (m_appCore->getDifficulty() != EASY) {
                m_nextEnemySpawnDistance /= 2;
            }
            return; //to not add another element if spawn distance valid
        } else {
            m_currentEnemySpawnDistance++;
        }

        //=== Add new Coins

        if (m_currentCoinSpawnDistance >= m_nextCoinSpawnDistance) {
            float pos_x = m_width;
            float pos_y = getGameFloorPosition() - RandomUtils::getUniformRandomNumber(0, 100);
            addANewMovableElement(pos_x, pos_y, COIN);

            m_currentCoinSpawnDistance = 0;
            m_nextCoinSpawnDistance = GameUtils::chooseSpawnDistance(m_nextCoinSpawnDistance, COIN);
            return;
        } else {
            m_currentCoinSpawnDistance++;
        }

        //=== Add new Bonus

        if (m_currentBonusSpawnDistance >= m_nextBonusSpawnDistance) {
            float pos_x = m_width;
            float pos_y = 0.63f * m_height;
            addANewMovableElement(pos_x, pos_y, PV_PLUS_BONUS);

            m_currentBonusSpawnDistance = 0;
            m_nextBonusSpawnDistance = GameUtils::chooseSpawnDistance(m_nextBonusSpawnDistance, PV_PLUS_BONUS);
            return;
        } else {
            m_currentBonusSpawnDistance++;
        }
    }
}

/**
 * @brief Handle Movable Elements Collisions
 * @warning It must be executed outside of the next step delay
 * to prevent high speed collisions skipping
 *
 * @author Arthur
 * @date 12/03/16 - 13/07/2019
 */
void GameModel::handleMovableElementsCollisions()
{
    for (MovableElement* element : m_movableElementsArray) {
        if (!element->isColliding() && element->getType() != PLAYER && element->collide(*m_player)) {
            //Apply different behaviours following element type
            switch (element->getType()) {
                case STANDARD_ENEMY:
                case TOTEM_ENEMY:
                case BLOCK_ENEMY:
                    handleEnemyCollision(element->getType());
                    break;
                case COIN:
                    handleCoinCollision();
                    break;
                case PV_PLUS_BONUS:
                case MEGA_BONUS:
                case FLY_BONUS:
                case SLOW_SPEED_BONUS:
                case SHIELD_BONUS:
                    handleBonusCollision(element->getType());
                    break;
                default:
                    Logger::printError("Undefined element type");
                    break;
            }
        }
    }
}

/**
 * @brief Handle Movable Elements Deletion
 * @warning The element pointer will only be deleted in destructor
 *
 * @author Arthur
 * @date 12/03/16 - 13/09/18
 */
void GameModel::handleMovableElementsDeletion()
{
    auto it = m_movableElementsArray.begin();
    while (it != m_movableElementsArray.end()) {
        if (((*it)->getPosX() + (*it)->getWidth()) < 0 || (*it)->isColliding()) {
            m_movableElementsArray.erase(it);
            it = m_movableElementsArray.end();
        } else {
            ++it;
        }
    }
}

/**
 * @brief Handle a collision between the player and an enemy
 *
 * @param enemyType the enemy type
 *
 * @author Arthur, Florian
 * @date 25/02/16 - 13/01/2019
 */
void GameModel::handleEnemyCollision(const MovableElementType& enemyType)
{
    if (m_player->getState() == MEGA) {
        //Earn points by flattening enemies
        m_appCore->increaseCurrentFlattenedEnemies();
        if (enemyType == STANDARD_ENEMY) {
            m_scoreBonusFlattenedEnemies += MEGA_BONUS_FLATTENED_STD;
        } else if (enemyType == TOTEM_ENEMY) {
            m_scoreBonusFlattenedEnemies += MEGA_BONUS_FLATTENED_TOTEM;
        } else {
            m_scoreBonusFlattenedEnemies += MEGA_BONUS_FLATTENED_BLOCK;
        }
    } else if (m_player->getState() == HARD_SHIELDED) {
        m_player->changeState(SHIELDED);
    } else if (m_player->getState() == SHIELDED) {
        m_player->changeState(NORMAL);
    } else {
        if (enemyType == STANDARD_ENEMY) {
            m_player->takeDamages(COLLISION_DAMAGE_STD * m_appCore->getDifficulty());
        } else if (enemyType == TOTEM_ENEMY) {
            m_player->takeDamages(COLLISION_DAMAGE_TOTEM * m_appCore->getDifficulty());
        } else {
            m_player->takeDamages(COLLISION_DAMAGE_BLOCK * m_appCore->getDifficulty());
        }
    }
}

/**
 * @brief Handle a collision between the player and a coin
 *
 * @author Arthur, Florian
 * @date 25/02/16 - 27/12/2017
 */
void GameModel::handleCoinCollision() const
{
    m_appCore->increaseCurrentCoinsCollected(
            m_appCore->findActivatedItem("doubler") ? 2 : 1);
}

/**
 * @brief Handle a collision between the player and a bonus
 *
 * @param bonusType the type of bonus having collided with player
 *
 * @author Arthur, Florian
 * @date 25/02/16 - 13/01/2019
 */
void GameModel::handleBonusCollision(const MovableElementType& bonusType)
{
    if (bonusType == PV_PLUS_BONUS) {
        m_player->heal(PV_BONUS_INCREASE);
    } else if (bonusType == MEGA_BONUS) {
        m_player->changeState(MEGA);
        m_bonusTimeout = milliseconds(m_appCore->findActivatedItem("shop_mega_plus")
                                              ? MEGA_TIMEOUT + ADDITIONAL_TIMEOUT
                                              : MEGA_TIMEOUT);
    } else if (bonusType == FLY_BONUS) {
        m_player->changeState(FLYING);
        m_bonusTimeout = milliseconds(m_appCore->findActivatedItem("shop_fly_plus")
                                              ? FLY_TIMEOUT + ADDITIONAL_TIMEOUT
                                              : FLY_TIMEOUT);
    } else if (bonusType == SLOW_SPEED_TIMEOUT) {
        m_gameState = RUNNING_SLOWLY;
        m_gameSpeed /= SLOW_SPEED_BONUS_DIVIDER;
        m_gameSlowSpeed = m_gameSpeed;
        m_bonusTimeout = milliseconds(SLOW_SPEED_TIMEOUT);
    } else if (bonusType == SHIELD_BONUS) {
        m_player->changeState(m_appCore->findActivatedItem("shop_shield_plus") ? HARD_SHIELDED : SHIELDED);
    } else {
        Logger::printError("Undefined bonus type");
    }
}

/**
 * @brief Handle the bonus effect duration
 * @details Decrease a timeout and process its expiration
 *
 * @author Arthur
 * @date 12/04/16 - 04/02/2018
 */
void GameModel::handleBonusTimeout()
{
    if (m_bonusTimeout.count() > milliseconds(0).count()) {
        m_bonusTimeout.operator-=(milliseconds(NEXT_STEP_DELAY));
    } else {
        if (m_player->getState() != SHIELDED && m_player->getState() != HARD_SHIELDED) {
            m_player->changeState(NORMAL);
        }

        if (m_gameState == RUNNING_SLOWLY) {
            m_gameState = RUNNING;
            if (m_gameSpeed == m_gameSlowSpeed) {
                m_gameSpeed *= 1.5;
            }
        }
    }
}

/**
 * @brief Check if game's current evolution allows
 * to authorize a zone transition as soon as possible
 *
 * @author Arthur
 * @date 30/04/16 - 13/01/2019
 */
void GameModel::conditionallyAllowZoneTransition()
{
    if (!m_inTransition
            && m_appCore->getGameMap().at("distance") != 0
            && m_appCore->getGameMap().at("distance") % ZONE_CHANGING_DISTANCE == 0) {
        m_isTransitionPossible = true;
    }
}

/**
 * @brief Conditionally trigger a game over
 * if player's life has ended
 *
 * @author Arthur
 * @date 27/03/2016 - 13/07/2019
 */
void GameModel::conditionallyTriggerGameOver()
{
    if (m_player->getLife() == Player::MIN_ENERGY) {
        m_gameState = OVER;
        m_appCore->calculateFinalScore(m_gameSpeed, m_scoreBonusFlattenedEnemies);
    }
}

/**
 * @brief Check if a position is free to use
 *
 * @param x element x-position
 * @param y element y-position
 * @return a boolean indicating if parameterized position is free
 *
 * @author Arthur
 * @date 08/03/2016 - 30/04/2016
 */
bool GameModel::checkIfPositionFree(float x, float y) const
{
    bool positionIsFree = true;
    auto it = m_movableElementsArray.begin();

    while (positionIsFree && it != m_movableElementsArray.end()) {
        if ((*it)->contains(x, y)) {
            positionIsFree = false;
        } else {
            ++it;
        }
    }

    return positionIsFree;
}

/**
 * @brief Add a new movable element to the game
 *
 * @param posX the initial x-position of the new element
 * @param posY the initial y-position of the new element
 * @param type the type of the new element
 *
 * @author Arthur, Florian
 * @date 25/02/2016 - 16/09/2018
 */
void GameModel::addANewMovableElement(float posX, float posY, int type)
{
    const float ELEMENT_MOVE_X = getGameSpeed() * (-1);
    MovableElement* newElement = nullptr;

    if (type == PLAYER) {
        m_player = new Player(posX, posY, ELEMENT_SIZE, ELEMENT_SIZE, 2.0, 18.0, getGameFloorPosition(),
                              static_cast<int>(m_width), static_cast<int>(0.515f * m_height));
        newElement = m_player;
    } else if (type == STANDARD_ENEMY) { //any enemy, transformation in CTOR
        newElement = new Enemy(posX, posY, ELEMENT_SIZE, ELEMENT_SIZE, ELEMENT_MOVE_X, ELEMENT_MOVE_Y);
    } else if (type == COIN) {
        newElement = new Coin(posX, posY, ITEM_SIZE, ITEM_SIZE, ELEMENT_MOVE_X, ELEMENT_MOVE_Y);
    } else if (type == PV_PLUS_BONUS) { //any bonus, transformation in CTOR
        newElement = new Bonus(posX, posY, ITEM_SIZE, ITEM_SIZE, ELEMENT_MOVE_X, ELEMENT_MOVE_Y);
    } else {
        Logger::printError("Undefined element type");
    }

    if (newElement == nullptr) {
        Logger::printError("NULL value : movable element can't be created");
    } else {
        m_newMovableElementsArray.insert(newElement);
        m_movableElementsArray.insert(newElement);
    }
}
