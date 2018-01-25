#include "GameModel.h"

using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::string;
using Bokoblin::SimpleLogger::Logger;

/**
 * Constructs a GameModel with the app common model
 * @author Arthur
 * @date 26/03/16 - 29/12/17
 *
 * @param width the app's width
 * @param height the app's height
 * @param dataBase the app's dataBase
 */
GameModel::GameModel(float width, float height, DataBase *dataBase) :
        AbstractModel(dataBase), m_width{width}, m_height{height}, m_gameState{RUNNING}, m_inTransition{false},
        m_isTransitionPossible{false}, m_currentZone{HILL}, m_gameSlowSpeed{0},
        m_currentEnemyTimeSpacing{0}, m_currentCoinTimeSpacing{0}, m_currentBonusTimeSpacing{0},
        m_lastTime{system_clock::now()}, m_bonusTimeout{0}
{
    //=== Initialize new game

    m_dataBase->launchNewGame();
    m_dataBase->fetchActivatedShopItems();

    addANewMovableElement(DEFAULT_PLAYER_X, GAME_FLOOR, PLAYER);

    if (m_dataBase->getDifficulty() == EASY)
        m_gameSpeed = DEFAULT_SPEED;
    else
        m_gameSpeed = 2 * DEFAULT_SPEED;

    //=== Initialize elements apparition time-spacing

    m_chosenCoinTimeSpacing = RandomUtils::getUniformRandomNumber(0, 10);       //Between 0 and 10 meters
    m_chosenEnemyTimeSpacing = RandomUtils::getUniformRandomNumber(10, 20);     //Between 10 and 20 meters
    m_chosenBonusTimeSpacing = RandomUtils::getUniformRandomNumber(100, 150);   //Between 100 and 150 meters
}


/**
 * Destructor
 * @author Arthur
 * @date 26/03/16 - 24/12/17
 */
GameModel::~GameModel()
{
    for (auto &element : m_movableElementsArray)
        delete element;

    m_movableElementsArray.clear();
}


//=== Getters

GameState GameModel::getGameState() const { return m_gameState; }
bool GameModel::isTransitionRunning() const { return m_inTransition; }
bool GameModel::isTransitionPossible() const { return m_isTransitionPossible; }
float GameModel::getGameSpeed() const { return m_gameSpeed; }
int GameModel::getBonusTimeout() const { return (int) (m_bonusTimeout.count() / 1000); } // return seconds
Zone GameModel::getCurrentZone() const { return m_currentZone; }
Player* GameModel::getPlayer() const { return m_player; }
const std::set<MovableElement*>& GameModel::getNewMElementsArray() const { return m_newMovableElementsArray; }


//=== Setters

void GameModel::setGameState(GameState state) { m_gameState = state; }
void GameModel::setTransitionState(bool inTransition) { m_inTransition = inTransition; }
void GameModel::setTransitionPossibleState(bool state) { m_isTransitionPossible = state; }
void GameModel::setCurrentZone(Zone z) { m_currentZone = z; }


/**
 * Handles game's evolution
 * (elements apparition, behaviours, deletion)
 * and game mode changing
 * @author Arthur
 * @date 21/02/16 - 03/11/17
 */
void GameModel::nextStep()
{
    system_clock::duration currentNextStepDelay = system_clock::now() - m_lastTime;

    if (m_gameState == RUNNING || m_gameState == RUNNING_SLOWLY)
    {
        //=== Handle Movable Elements Collisions

        //outside of delay otherwise some high speed collisions are not triggered
        handleMovableElementsCollisions();

        system_clock::duration nextStepDelay = milliseconds(NEXT_STEP_DELAY);

        if (currentNextStepDelay.count() > nextStepDelay.count())
        {
            //=== Update distance and gameSpeed

            if (m_gameSpeed < SPEED_LIMIT && m_gameState != RUNNING_SLOWLY)
            {
                m_gameSpeed += SPEED_STEP;
            }

            m_dataBase->increaseCurrentDistance(m_gameSpeed/5);


            //=== Handle Movable Elements Creation & Deletion

            if (!m_isTransitionPossible)
                handleMovableElementsCreation();

            handleMovableElementsDeletion();


            //=== Handle bonus timeout expiration

            if (m_bonusTimeout.count() > milliseconds(0).count())
            {
                m_bonusTimeout.operator-=(milliseconds(NEXT_STEP_DELAY));
            }
            else
            {
                if (m_player->getState() != SHIELD)
                {
                    m_player->changeState(NORMAL);
                }

                if (m_gameState == RUNNING_SLOWLY)
                {
                    m_gameState = RUNNING;
                    if (m_gameSpeed == m_gameSlowSpeed)
                        m_gameSpeed *= 1.5;
                }
            }


            //=== Handle transition status

            if (m_dataBase->getCurrentDistance() != 0
                && m_dataBase->getCurrentDistance()%ZONE_CHANGING_DISTANCE == 0)
                m_isTransitionPossible = true;


            //=== Go to Game Over

            if (m_player->getLife() == 0)
                m_gameState = OVER;

            m_lastTime = system_clock::now();
        }
    }
    else if (m_gameState == OVER)
    {
        m_dataBase->setCurrentScore(m_gameSpeed);
    }
}


/**
 * Calculates the time-spacing before creating
 * a new element of the same type
 * @author Arthur
 * @date 12/03/16 - 29/12/17
 *
 * @param elementType the type of element that was just created
 */
void GameModel::chooseTimeSpacing(int elementType)
{
    switch (elementType)
    {
        case STANDARD_ENEMY: //Any enemy though
        {
            if (m_chosenEnemyTimeSpacing > 40)
                m_chosenEnemyTimeSpacing = RandomUtils::getUniformRandomNumber(0, 30); //Between 0 and 30 meters
            else if (m_chosenEnemyTimeSpacing < 10)
                m_chosenEnemyTimeSpacing = RandomUtils::getUniformRandomNumber(10, 50); //Between 10 and 50 meters
            else
                m_chosenEnemyTimeSpacing = RandomUtils::getUniformRandomNumber(0, 40); //Between 0 and 40 meters

            if (m_dataBase->getDifficulty() != EASY)
                m_chosenEnemyTimeSpacing /= 2;
        }
            break;
        case COIN:
        {
            if (m_chosenCoinTimeSpacing > 10)
                m_chosenCoinTimeSpacing = RandomUtils::getUniformRandomNumber(0, 10); //0 to 10m
            else if (m_chosenCoinTimeSpacing < 10)
                m_chosenCoinTimeSpacing = RandomUtils::getUniformRandomNumber(10, 20); //10 to 20m
            else
                m_chosenCoinTimeSpacing = RandomUtils::getUniformRandomNumber(0, 20); //0 to 20m
        }
            break;
        case PV_PLUS_BONUS: //Any bonus though
        {
            if (m_chosenBonusTimeSpacing > 300)
                m_chosenBonusTimeSpacing = RandomUtils::getUniformRandomNumber(200, 300); //200 to 300m
            else if (m_chosenBonusTimeSpacing < 275)
                m_chosenBonusTimeSpacing = RandomUtils::getUniformRandomNumber(300, 400);  //300 to 400m
            else
                m_chosenBonusTimeSpacing = RandomUtils::getUniformRandomNumber(200, 400); //200 to 400m
        }
            break;
        default:
            break;
    }
}


/**
 * Checks if a position is free to use
 * @author Arthur
 * @date 08/03/16 - 30/04/16
 *
 * @param x element x-position
 * @param y element y-position
 * @return a boolean indicating if parameterized position is free
 */
bool GameModel::checkIfPositionFree(float x, float y) const
{
    bool positionIsFree =true;
    std::set<MovableElement*>::iterator it=m_movableElementsArray.begin();

    while (positionIsFree &&  it != m_movableElementsArray.end())
    {
        if ((*it)->contains(x, y))
            positionIsFree = false;
        else
            ++it;
    }

    return positionIsFree;
}


/**
 * NewMovableElement vector cleaning
 * @author Arthur, Florian
 * @date 02/03/16
 */
void GameModel::clearNewMovableElementList()
{
    m_newMovableElementsArray.clear();
}


/**
 * Elements Moving (enemies, bonus, ...)
 * @author Arthur
 * @date 06/03/16 - 26/03/16
 *
 * @param currentElement the element to move
 */
void GameModel::moveMovableElement(MovableElement *currentElement)
{
    if (currentElement == m_player)
        currentElement->move();
    else if (currentElement != nullptr)
    {
        currentElement->setMoveX(-1*m_gameSpeed);
        currentElement->move();
    }
}

/**
 * Handles Elements Creation
 * @author Arthur
 * @date 12/04/16 - 29/12/17
 */
void GameModel::handleMovableElementsCreation()
{
    if (checkIfPositionFree(m_width, GAME_FLOOR))
    {
        //=== Add new enemies

        if (m_currentEnemyTimeSpacing >= m_chosenEnemyTimeSpacing)
        {
            float pos_x = m_width;
            float pos_y = GAME_FLOOR;
            addANewMovableElement(pos_x, pos_y, STANDARD_ENEMY);

            m_currentEnemyTimeSpacing = 0;
            chooseTimeSpacing(STANDARD_ENEMY);
            return; //to not add another element if time-spacing valid
        }
        else m_currentEnemyTimeSpacing++;

        //=== Add new Coins

        if (m_currentCoinTimeSpacing >= m_chosenCoinTimeSpacing)
        {
            float pos_x = m_width;
            float pos_y = GAME_FLOOR - RandomUtils::getUniformRandomNumber(0, 100);
            addANewMovableElement(pos_x, pos_y, COIN);

            m_currentCoinTimeSpacing = 0;
            chooseTimeSpacing(COIN);
            return;
        }
        else m_currentCoinTimeSpacing++;

        //=== Add new Bonus

        if (m_currentBonusTimeSpacing >= m_chosenBonusTimeSpacing)
        {
            float pos_x = m_width;
            float pos_y = BONUS_ROW;
            addANewMovableElement(pos_x, pos_y, PV_PLUS_BONUS);

            m_currentBonusTimeSpacing = 0;
            chooseTimeSpacing(PV_PLUS_BONUS);
            return;
        }
        else m_currentBonusTimeSpacing++;
    }
}


/**
 * New MovableElement adding
 * @author Arthur, Florian
 * @date 25/02/16 - 29/12/17
 *
 * @param posX the initial x-position of the new element
 * @param posY the initial y-position of the new element
 * @param type the type of the new element
 */
void GameModel::addANewMovableElement(float posX, float posY, int type)
{
    const float ELEMENT_MOVE_X = getGameSpeed()*(-1);
    MovableElement *m_newMElement = nullptr;

    if (type == PLAYER)
    {
        m_player = new Player(posX, posY, 30, 30, 2.0, 18.0);
        m_newMElement = m_player;
    }
    else if (type == STANDARD_ENEMY)//any enemy, transformation in CTOR
    {
        m_newMElement = new Enemy(posX, posY, 30, 30, ELEMENT_MOVE_X, ELEMENT_MOVE_Y);
    }
    else if (type == COIN)
    {
        m_newMElement = new Coin(posX, posY, 25, 25, ELEMENT_MOVE_X, ELEMENT_MOVE_Y);
    }
    else if (type == PV_PLUS_BONUS) //any bonus, transformation in CTOR
    {
        m_newMElement = new Bonus(posX, posY, 25, 25, ELEMENT_MOVE_X, ELEMENT_MOVE_Y);
    }
    else
    {
        Logger::printErrorOnConsole("Undefined element type");
    }

    if (m_newMElement == nullptr)
    {
        Logger::printErrorOnConsole("NULL value : movable element can't be created");
    }
    else
    {
        m_newMovableElementsArray.insert(m_newMElement);
        m_movableElementsArray.insert(m_newMElement);
    }
}


/**
 * Handles a collision between the player and an enemy
 * @author Arthur, Florian
 * @date 25/02/16 - 27/12/17
 *
 * @param enemyType the enemy type
 */
void GameModel::handleEnemyCollision(MovableElementType enemyType)
{
    if (m_player->getState() == MEGA) {
        //Earn points by flattening enemies
        if (enemyType == STANDARD_ENEMY)
            m_dataBase->increaseCurrentFlattenedEnemies(MEGA_BONUS_FLATTENED_STD);
        else if (enemyType == TOTEM_ENEMY)
            m_dataBase->increaseCurrentFlattenedEnemies(MEGA_BONUS_FLATTENED_TOTEM);
        else
            m_dataBase->increaseCurrentFlattenedEnemies(MEGA_BONUS_FLATTENED_BLOCK);
    }
    else if (m_player->getState() == SHIELD
             && m_bonusTimeout.count() != milliseconds(SHIELD_TIMEOUT).count())
    {
        if (m_dataBase->findActivatedItem("shieldPlus"))
            m_bonusTimeout = milliseconds(SHIELD_TIMEOUT);
        else
            m_player->changeState(NORMAL);
    }
    else if (m_player->getState() == SHIELD)
    {
        m_player->changeState(NORMAL);
    }
    else {
        if (m_dataBase->getDifficulty() == EASY)
        {
            if (enemyType == STANDARD_ENEMY)
                m_player->setLife(m_player->getLife() - COLLISION_DAMAGE_STD);
            else if (enemyType == TOTEM_ENEMY)
                m_player->setLife(m_player->getLife() - COLLISION_DAMAGE_TOTEM);
            else
                m_player->setLife(m_player->getLife() - COLLISION_DAMAGE_BLOCK);
        }
        else
        {
            if (enemyType == STANDARD_ENEMY)
                m_player->setLife(m_player->getLife() - 2 * COLLISION_DAMAGE_STD);
            else if (enemyType == TOTEM_ENEMY)
                m_player->setLife(m_player->getLife() - 2 * COLLISION_DAMAGE_TOTEM);
            else
                m_player->setLife(m_player->getLife() - 2 * COLLISION_DAMAGE_BLOCK);
        }
    }
}


/**
 * Handles a collision between the player and a coin
 * @author Arthur, Florian
 * @date 25/02/16 - 27/12/17
 */
void GameModel::handleCoinCollision() const
{
    m_dataBase->increaseCurrentCoinsCollected(
            m_dataBase->findActivatedItem("doubler") ? 2 : 1);
}


/**
 * Handles a collision between the player and a bonus
 * @author Arthur, Florian
 * @date 25/02/16 - 27/12/17
 */
void GameModel::handleBonusCollision(MovableElementType bonusType)
{
    if (bonusType == PV_PLUS_BONUS)
    {
        m_player->setLife(m_player->getLife() + PV_BONUS_INCREASE);
    }
    else if (bonusType == MEGA_BONUS)
    {
        m_player->changeState(MEGA);
        m_bonusTimeout = milliseconds(m_dataBase->findActivatedItem("megaPlus")
                                              ? MEGA_TIMEOUT + ADDITIONAL_TIMEOUT
                                              : MEGA_TIMEOUT);
    }
    else if (bonusType == FLY_BONUS)
    {
        m_player->changeState(FLY);
        m_bonusTimeout = milliseconds(m_dataBase->findActivatedItem("flyPlus")
                                              ? FLY_TIMEOUT + ADDITIONAL_TIMEOUT
                                              : FLY_TIMEOUT);
    }
    else if (bonusType == SLOW_SPEED_TIMEOUT)
    {
        m_gameState = RUNNING_SLOWLY;
        m_gameSpeed /= SLOW_SPEED_BONUS_DIVIDER;
        m_gameSlowSpeed = m_gameSpeed;
        m_bonusTimeout = milliseconds(SLOW_SPEED_TIMEOUT);
    }
    else if (bonusType == SHIELD_BONUS)
    {
        m_player->changeState(SHIELD);
    }
    else
    {
        Logger::printErrorOnConsole("Undefined bonus type");
    }
}

/**
 * Handles Movable Elements Collisions
 * @author Arthur
 * @date 12/03/16 - 27/12/17
 */
void GameModel::handleMovableElementsCollisions()
{
    for (MovableElement* element : m_movableElementsArray)
    {
        if (!element->isColliding() && element->getType() != PLAYER && m_player->collision(*element))
        {
            element->setColliding(true);

            //Apply different behaviours following element type
            switch (element->getType())
            {
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
    while(it!=m_movableElementsArray.end())
    {
        if (((*it)->getPosX() + (*it)->getWidth()) < 0
            || (*it)->isColliding())
        {
            m_movableElementsArray.erase(it);
            it = m_movableElementsArray.end();
        }
        else
            ++it;
    }
}
