#include "../header/GameModel.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 26/03 - 30/04
*********************************************/
GameModel::GameModel(const Model& model) :
    Model(model), m_pauseState{false}, m_endState{false}, m_inTransition{false},
    m_isTransitionPossible{false}, m_isSavePossible{true},
    m_gameSpeed{DEFAULT_SPEED}, m_currentZone{1},
    m_currentEnemyInterdistance{0}, m_currentCoinInterdistance{0}, m_currentBonusInterdistance{0},
    m_lastTime{chrono::system_clock::now()}, m_bonusStopTime{chrono::milliseconds(0)}, m_bonusTimeout{0}
{
    srand(time(NULL));
    //default interdistances (in meters) for elements
    m_chosenEnemyInterdistance = 10 +rand()%10;
    m_chosenCoinInterdistance = rand()%10;
    m_chosenBonusInterdistance = 100 + rand()%50;
    //create player
    addANewMovableElement(50, GAME_FLOOR, PLAYER);

    m_dataBase->resetCurrentGame();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 26/03
*********************************************/
GameModel::~GameModel()
{
    for (set<MovableElement*>::iterator it = m_movableElementsArray.begin(); it!=m_movableElementsArray.end(); ++it)
        delete *it;

    m_movableElementsArray.clear();
}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 21/02 - 2/05
    @author Florian @date 21/02 - 25/02
*********************************************/
bool GameModel::getPauseState() const { return m_pauseState; }
bool GameModel::getEndState() const { return m_endState; }
bool GameModel::getTransitionStatus() const { return m_inTransition; }
bool GameModel::getTransitionPossibleStatus() const { return m_isTransitionPossible; }
bool GameModel::getSaveStatus() const { return m_isSavePossible; }
float GameModel::getGameSpeed() const { return m_gameSpeed; }
int GameModel::getBonusTimeout() const { return m_bonusTimeout.count()/1000; }
int GameModel::getCurrentZone() const { return m_currentZone; }
Player* GameModel::getPlayer() const { return m_player; }
const set<MovableElement*>& GameModel::getNewMElementsArray() const { return m_newMovableElementsArray; }

/********************************************
    Setters
*********************************************
    @author Arthur  @date 8/03 - 30/04
*********************************************/
void GameModel::setPauseState(bool state) { m_pauseState = state; }
void GameModel::setEndState(bool state) { m_endState = state;}
void GameModel::setTransitionStatus(bool status) { m_inTransition = status; }
void GameModel::setTransitionPossibleStatus(bool status) { m_isTransitionPossible = status; }
void GameModel::setSaveStatus(bool status) { m_isSavePossible = status; }
void GameModel::setCurrentZone(int number) { m_currentZone = number; }


/********************************************
    Next Step
*********************************************
    @author Arthur  @date 21/02 - 28/04
*********************************************/
void GameModel::nextStep()
{
    chrono::system_clock::duration nextStepDelay = chrono::system_clock::now() - m_lastTime;

	if (m_pauseState == false && m_endState == false)
	{
	    //=== Handle Movable Elements Collisions

        handleMovableElementsCollisions(); //outside of delay otherwise some highspeed collisions are not triggered

		if ( nextStepDelay > chrono::milliseconds( 100 ) )
		{
            //=== Update distance and gamespeed

		    if ( m_difficulty == NORMAL_DIFFICULTY && m_gameSpeed < 16 && chrono::system_clock::now() >= m_bonusStopTime)
            {
                m_gameSpeed += 0.01;
            }
            else if ( m_difficulty != NORMAL_DIFFICULTY && m_gameSpeed < 18 && chrono::system_clock::now() >= m_bonusStopTime)
            {
                if (m_gameSpeed == 4.0) m_gameSpeed = 8.0;
                m_gameSpeed += 0.02;
            }
			m_dataBase->setCurrentDistance(1 + 2*m_difficulty);

			//=== Handle Movable Elements Creation & Deletion

			if (m_isTransitionPossible == false)
                handleMovableElementsCreation();

            handleMovableElementsDeletion();


            //=== Bonus timeout & ending

            auto timeout = chrono::duration_cast<chrono::milliseconds>(m_bonusStopTime - chrono::system_clock::now());
            m_bonusTimeout = timeout;

            if ( chrono::system_clock::now() >= m_bonusStopTime)
            {
                if ( m_player->getState() == OTHER)
                    m_gameSpeed *=2;
                m_player->changeState(NORMAL);
            }


            //=== Handle transition status

            if ( m_dataBase->getCurrentDistance() !=0 && m_difficulty == NORMAL_DIFFICULTY
                && m_dataBase->getCurrentDistance()%500 ==0) //at each 500 meters
                m_isTransitionPossible = true;
            if ( m_dataBase->getCurrentDistance() !=0 && m_difficulty == MASTER_DIFFICULTY
                && m_dataBase->getCurrentDistance()%2000 ==0) //at each 2000 meters
                m_isTransitionPossible = true;


            //=== Handle Game's end

            if (m_player->getLife() == 0)
                m_endState = true;

            m_lastTime = chrono::system_clock::now();
        }
    }
    else if (m_endState == true)
    {
        m_dataBase->setCurrentScore(m_gameSpeed);
    }
}


/********************************************
    choose the interdistance between elements
*********************************************
    @author Arthur  @date  12/03 - 18/05
*********************************************/
void GameModel::chooseInterdistance(int elementType)
{
    //allows to calculate interdistance in different situations

    if  ( elementType  == STANDARDENEMY ) //any enemy
    {
        if (m_chosenEnemyInterdistance > 40)
            m_chosenEnemyInterdistance = abs(rand()%31); //0 to 30m
        else if  ( m_chosenEnemyInterdistance < 10)
            m_chosenEnemyInterdistance = 10 + abs(rand()%41); //10 to 50m
        else
            m_chosenEnemyInterdistance = abs(rand()%41); //0 to 40m

        if ( m_difficulty != NORMAL_DIFFICULTY ) m_chosenEnemyInterdistance /= 3;
    }

    else if ( elementType == COIN )
    {
        if (m_chosenCoinInterdistance > 20)
            m_chosenCoinInterdistance = abs(rand()%21); //0 to 20m
        else if  ( m_chosenCoinInterdistance < 10)
            m_chosenCoinInterdistance = 15 + abs(rand()%26); //15 to 40m
        else
            m_chosenCoinInterdistance = abs(rand()%31); //0 to 30m
    }

    else if ( elementType == PVPLUSBONUS ) //any Bonus
    {
        if (m_chosenBonusInterdistance > 300)
            m_chosenBonusInterdistance = 200 + abs(rand()%101); //200 to 300m
        else if  ( m_chosenBonusInterdistance < 275)
            m_chosenBonusInterdistance = 300 + abs(rand()%101); //300 to 400m
        else
            m_chosenBonusInterdistance = 200 + abs(rand()%201); //200 to 400m
    }
}


/********************************************
    check if a position is free to use
*********************************************
    @author Arthur  @date  8/03 - 30/04
*********************************************/
bool GameModel::checkIfPositionFree(float x, float y) const
{
    bool positionIsFree =true;
    set<MovableElement*>::iterator it=m_movableElementsArray.begin();

    while (positionIsFree &&  it != m_movableElementsArray.end() )
    {
        if ( (*it)->contains(x,y) )
            positionIsFree = false;
        else
            ++it;
    }

    return positionIsFree;
}


/********************************************
    NewMovableElement vector cleaning
*********************************************
    @author Arthur  @date 2/03 - 26/03
    @author Florian @date 2/03
*********************************************/
void GameModel::clearNewMovableElementList()
{
    m_newMovableElementsArray.clear();
}


/********************************************
    Elements Moving (enemies, bonus, ...)
*********************************************
    @author Arthur  @date 6/03 - 26/03
*********************************************/
void GameModel::moveMovableElement(MovableElement *currentElement)
{
    if( currentElement == m_player)
        currentElement->move();
    else if( currentElement != NULL )
    {
        currentElement->setMoveX(-1*m_gameSpeed);
        currentElement->move();
    }
}

/********************************************
    Handle Elements Creation
*********************************************
    @author Arthur  @date 12/04
*********************************************/
void GameModel::handleMovableElementsCreation()
{
    //=== Add new enemies

    if (m_currentEnemyInterdistance >= m_chosenEnemyInterdistance)
    {
        if (checkIfPositionFree(m_width, GAME_FLOOR) == true)
        {
            addANewMovableElement(m_width, GAME_FLOOR, STANDARDENEMY);
            m_currentEnemyInterdistance = 0;
            chooseInterdistance(STANDARDENEMY);
        }
    }
    else m_currentEnemyInterdistance++;

    //=== Add new Coins

    if (m_currentCoinInterdistance >= m_chosenCoinInterdistance)
    {
        if (checkIfPositionFree(m_width, GAME_FLOOR) == true)
        {
            addANewMovableElement(m_width, GAME_FLOOR-100, COIN);
            m_currentCoinInterdistance = 0;
            chooseInterdistance(COIN);
        }
    }
    else m_currentCoinInterdistance++;

    //=== Add new Bonus

    if (m_currentBonusInterdistance >= m_chosenBonusInterdistance)
    {
        if (checkIfPositionFree(m_width, GAME_FLOOR) == true)
        {
            addANewMovableElement(m_width, GAME_FLOOR-100, PVPLUSBONUS);
            m_currentBonusInterdistance = 0;
            chooseInterdistance(PVPLUSBONUS);
        }
    }
    else m_currentBonusInterdistance++;
}


/********************************************
    New MovableElement  Adding
*********************************************
    @author Arthur  @date 25/02 - 11/04
    @author Florian @date 2/03
*********************************************/
void GameModel::addANewMovableElement(float posX, float posY, int type)
{
    MovableElement *m_newMElement = nullptr;
    if (type == PLAYER)
    {
        m_player = new Player(posX, posY, 30, 30, 2.0, 18.0);
        m_newMElement = m_player;
    }
    else if (type == STANDARDENEMY)//any enemy, transformation in CTOR
    {
        m_newMElement = new Enemy(posX, posY, 30, 30, getGameSpeed()*(-1), 0);
    }
    else if (type == COIN)
    {
        m_newMElement = new Coin(posX, posY, 25, 25, getGameSpeed()*(-1), 0);
    }
    else if (type == PVPLUSBONUS) //any bonus, transformation in CTOR
    {
        m_newMElement = new Bonus(posX, posY, 25, 25, getGameSpeed()*(-1), 0);
    }
    assert(m_newMElement != nullptr);

    if (m_movableElementsArray.find(m_newMElement) == m_movableElementsArray.end())
    {
        m_newMovableElementsArray.insert( m_newMElement );
        m_movableElementsArray.insert( m_newMElement );
    }
    m_newMElement = nullptr;
}


/********************************************
    Handle Movable Elements Collisions
*********************************************
    @author Arthur  @date 12/03 - 18/05
*********************************************/
void GameModel::handleMovableElementsCollisions()
{
    set<MovableElement*>::const_iterator it;
    for (it = m_movableElementsArray.begin(); it !=m_movableElementsArray.end(); ++it)
    {
        if ( (*it)->getCollisionState() == false && (*it)->getType() != PLAYER && m_player->collision(**it))
        {
            (*it)->setCollisionState(true);

            if ( (*it)->getType() == STANDARDENEMY && m_player->getState() != 1 )
            {
                if (m_difficulty == NORMAL_DIFFICULTY)
                    m_player->setLife(m_player->getLife()-10);
                else if (m_difficulty == MASTER_DIFFICULTY)
                    m_player->setLife(m_player->getLife()-20);
            }
            else if ( (*it)->getType() == STANDARDENEMY && m_player->getState() == 1 )
                m_dataBase->setCurrentFlattenedEnemies(100);


            else if ( (*it)->getType() == TOTEMENEMY && m_player->getState() != 1)
            {
                if (m_difficulty == NORMAL_DIFFICULTY)
                    m_player->setLife(m_player->getLife()-15);
                else if (m_difficulty == MASTER_DIFFICULTY)
                    m_player->setLife(m_player->getLife()-30);
            }
            else if ( (*it)->getType() == TOTEMENEMY && m_player->getState() == 1 )
                m_dataBase->setCurrentFlattenedEnemies(300);

            else if ( (*it)->getType() == BLOCKENEMY && m_player->getState() != 1)
            {
                if (m_difficulty == NORMAL_DIFFICULTY)
                    m_player->setLife(m_player->getLife()-25);
                else if (m_difficulty == MASTER_DIFFICULTY)
                    m_player->setLife(m_player->getLife()-50);
            }
            else if ( (*it)->getType() == BLOCKENEMY && m_player->getState() == 1 )
                m_dataBase->setCurrentFlattenedEnemies(500);

            else if ( (*it)->getType() == COIN)
                m_dataBase->setCurrentCoinsCollected(1);

            else if ( (*it)->getType() == PVPLUSBONUS)
                m_player->setLife(m_player->getLife()+10);

            else if ( (*it)->getType() == MEGABONUS) //stop Mega bonus effect in 10s
            {
                m_player->changeState(MEGA);
                m_bonusStopTime = chrono::system_clock::now() + chrono::milliseconds(10000);
            }

            else if ( (*it)->getType() == FLYBONUS) //stop Fly bonus effect in 15s
            {
                m_player->changeState(FLY);
                m_bonusStopTime = chrono::system_clock::now() + chrono::milliseconds(15000);
            }

            else if ( (*it)->getType() == SLOWSPEEDBONUS) //stop SlowDown bonus effect in 20s
            {
                m_gameSpeed = m_gameSpeed/2;
                m_player->changeState(OTHER);
                m_bonusStopTime = chrono::system_clock::now() + chrono::milliseconds(20000);
            }
        }
    }
}

/********************************************
    Handle Movable Elements Deletion
*********************************************
    @author Arthur  @date 12/03 - 11/04
*********************************************/
void GameModel::handleMovableElementsDeletion()
{
    set<MovableElement*>::iterator it = m_movableElementsArray.begin();
    while( it!=m_movableElementsArray.end() )
    {
        if ( ( (*it)->getPosX() + (*it)->getWidth() ) < 0 || (*it)->getCollisionState() == true )
        {
            /**<  note : do not delete the pointer, it is still used in the game view */
            m_movableElementsArray.erase(it);
            it = m_movableElementsArray.end();
        }
        else
            ++it;
    }
}
