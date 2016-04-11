#include "../header/Model.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 21/02 - 31/03
    @author Florian @date 21/02 - 2/03
*********************************************/
Model::Model(float width, float height, const chrono::_V2::system_clock::time_point beginTime)  :
    m_width(width), m_height(height), m_programBeginningTime{beginTime}
{
    m_introState = true;
    m_menuState = false;
    m_gameState = false;
    m_resetGameState = false;
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 21/02 - 26/03
    @author Florian @date 21/02 - 2/03
*********************************************/
Model::~Model()
{
}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 21/02 - 31/03
    @author Florian @date 21/02 - 25/02
*********************************************/
bool Model::getIntroState() const {return m_introState;}
bool Model::getMenuState() const {return m_menuState;}
bool Model::getGameState() const {return m_gameState;}
bool Model::getResetGameState() const {return m_resetGameState;}
chrono::system_clock::time_point Model::getProgramBeginningTime() const { return m_programBeginningTime; }


/********************************************
    Setters
*********************************************
    @author Arthur  @date 8/03 - 31/03
*********************************************/
void Model::setIntroState(bool state) {m_introState = state;}
void Model::setMenuState(bool state) {m_menuState = state;}
void Model::setGameState(bool state) {m_gameState = state;}
void Model::setResetGameState(bool state) {m_resetGameState = state;}


/********************************************
    Next Step
*********************************************
    @author Arthur  @date 21/02 - 27/03
*********************************************/
void Model::nextStep()
{ }
