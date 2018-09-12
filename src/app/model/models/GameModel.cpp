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
 * Constructs the game model
 * with app's width, height and core
 *
 * @param width the app's width
 * @param height the app's height
 * @param appCore the app's core singleton
 *
 * @author Arthur
 * @date 26/03/16 - 05/09/18
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
 * Destructor
 * @author Arthur
 * @date 26/03/16 - 24/12/17
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
bool GameModel::isTransitionRunning() const { return m_inTransition; }
bool GameModel::isTransitionPossible() const { return m_isTransitionPossible; }
float GameModel::getGameSpeed() const { return m_gameSpeed; }
int GameModel::getBonusTimeout() const { return static_cast<int>(m_bonusTimeout.count() / 1000); } // return seconds
Zone GameModel::getCurrentZone() const { return m_currentZone; }
Player* GameModel::getPlayer() const { return m_player; }
const std::set<MovableElement*>& GameModel::getNewMElementsArray() const { return m_newMovableElementsArray; }
unsigned int GameModel::getGameFloorPosition() const { return static_cast<unsigned int>(0.8f * m_height); }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void GameModel::setGameState(GameState state) { m_gameState = state; }
void GameModel::setCurrentZone(Zone z) { m_currentZone = z; }
void GameModel::setTransitionState(bool inTransition) { m_inTransition = inTransition; }
void GameModel::disableTransitionPossibility() { m_isTransitionPossible = false; }


//------------------------------------------------
//          PUBLIC METHODS
//------------------------------------------------

/**
 * Handles game mode changing and game's evolution
 * (elements apparition, behaviours, deletion)
 *
 * @author Arthur
 * @date 21/02/16 - 04/02/18
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
    } else if (m_gameState == OVER) {
        m_appCore->calculateFinalScore(m_gameSpeed, m_scoreBonusFlattenedEnemies);
    }
}

/**
 * Elements Moving (enemies, bonus, ...)
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
        currentElement->setMoveX(-1 * m_gameSpeed);
        currentElement->move();
    }
}


/**
 * NewMovableElement vector cleaning
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
 * Handles speed and distance increase
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
 * Handles Elements Creation
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
            m_nextCoinSpawnDistance =  GameUtils::chooseSpawnDistance(m_nextCoinSpawnDistance, COIN);
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
            m_nextBonusSpawnDistance =  GameUtils::chooseSpawnDistance(m_nextBonusSpawnDistance, PV_PLUS_BONUS);
            return;
        } else {
            m_currentBonusSpawnDistance++;
        }
    }
}


/**
 * Handles Movable Elements Collisions. \n
 * It must be executed outside of the next step delay
 * to prevent high speed collisions skipping
 *
 * @author Arthur
 * @date 12/03/16 - 27/12/17
 */
void GameModel::handleMovableElementsCollisions()
{
    for (MovableElement* element : m_movableElementsArray) {
        if (!element->isColliding() && element->getType() != PLAYER && m_player->collision(*element)) {
            element->setColliding(true);

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
                    Logger::printErrorOnConsole("Undefined element type");
                    break;
            }
        }
    }
}


/**
 * Handles Movable Elements Deletion \n
 * Note : Pointers will only be deleted in Dtor
 *
 * @author Arthur
 * @date 12/03/16 - 11/04/16
 */
void GameModel::handleMovableElementsDeletion()
{
    std::set<MovableElement*>::iterator it = m_movableElementsArray.begin();
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
 * Handles a collision between the player and an enemy
 *
 * @param enemyType the enemy type
 *
 * @author Arthur, Florian
 * @date 25/02/16 - 04/02/18
 */
void GameModel::handleEnemyCollision(MovableElementType enemyType)
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
            m_player->setLife(m_player->getLife() - (COLLISION_DAMAGE_STD * m_appCore->getDifficulty()));
        } else if (enemyType == TOTEM_ENEMY) {
            m_player->setLife(m_player->getLife() - (COLLISION_DAMAGE_TOTEM * m_appCore->getDifficulty()));
        } else {
            m_player->setLife(m_player->getLife() - (COLLISION_DAMAGE_BLOCK * m_appCore->getDifficulty()));
        }
    }
}


/**
 * Handles a collision between the player and a coin
 *
 * @author Arthur, Florian
 * @date 25/02/16 - 27/12/17
 */
void GameModel::handleCoinCollision() const
{
    m_appCore->increaseCurrentCoinsCollected(
            m_appCore->findActivatedItem("doubler") ? 2 : 1);
}


/**
 * Handles a collision between the player and a bonus
 *
 * @param bonusType the type of bonus having collided with player
 *
 * @author Arthur, Florian
 * @date 25/02/16 - 04/02/18
 */
void GameModel::handleBonusCollision(MovableElementType bonusType)
{
    if (bonusType == PV_PLUS_BONUS) {
        m_player->setLife(m_player->getLife() + PV_BONUS_INCREASE);
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
        Logger::printErrorOnConsole("Undefined bonus type");
    }
}


/**
 * Handles the bonus timeout
 * in order to decrease it or to process its expiration
 *
 * @author Arthur
 * @date 12/04/16 - 04/02/18
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
 * Checks if game's current evolution allows
 * to authorize a zone transition as soon as possible
 *
 * @author Arthur
 * @date 30/04/16 - 04/02/18
 */
void GameModel::conditionallyAllowZoneTransition()
{
    if (!m_inTransition
            && m_appCore->getCurrentDistance() != 0
            && m_appCore->getCurrentDistance() % ZONE_CHANGING_DISTANCE == 0) {
                m_isTransitionPossible = true;
    }
}


/**
 * Conditionally triggers a game over if
 * player's life has ended
 *
 * @author Arthur
 * @date ??/0?/16 - 04/02/18
 */
void GameModel::conditionallyTriggerGameOver()
{
    if (m_player->getLife() == Player::MIN_LIFE) {
        m_gameState = OVER;
    }
}


/**
 * Checks if a position is free to use
 *
 * @param x element x-position
 * @param y element y-position
 * @return a boolean indicating if parameterized position is free
 *
 * @author Arthur
 * @date 08/03/16 - 30/04/16
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
 * New MovableElement adding
 *
 * @param posX the initial x-position of the new element
 * @param posY the initial y-position of the new element
 * @param type the type of the new element
 *
 * @author Arthur, Florian
 * @date 25/02/16 - 06/09/18
 */
void GameModel::addANewMovableElement(float posX, float posY, int type)
{
    const float ELEMENT_MOVE_X = getGameSpeed() * (-1);
    MovableElement* newElement = nullptr;

    if (type == PLAYER) {
        m_player = new Player(posX, posY, ELEMENT_SIZE, ELEMENT_SIZE, 2.0, 18.0, getGameFloorPosition(), (int) m_width);
        newElement = m_player;
    } else if (type == STANDARD_ENEMY)//any enemy, transformation in CTOR
    {
        newElement = new Enemy(posX, posY, ELEMENT_SIZE, ELEMENT_SIZE, ELEMENT_MOVE_X, ELEMENT_MOVE_Y);
    } else if (type == COIN) {
        newElement = new Coin(posX, posY, ITEM_SIZE, ITEM_SIZE, ELEMENT_MOVE_X, ELEMENT_MOVE_Y);
    } else if (type == PV_PLUS_BONUS) //any bonus, transformation in CTOR
    {
        newElement = new Bonus(posX, posY, ITEM_SIZE, ITEM_SIZE, ELEMENT_MOVE_X, ELEMENT_MOVE_Y);
    } else {
        Logger::printErrorOnConsole("Undefined element type");
    }

    if (newElement == nullptr) {
        Logger::printErrorOnConsole("NULL value : movable element can't be created");
    } else {
        m_newMovableElementsArray.insert(newElement);
        m_movableElementsArray.insert(newElement);
    }
}
