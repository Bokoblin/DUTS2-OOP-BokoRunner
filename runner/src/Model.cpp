#include "../header/Model.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 21/02 - 6/05
    @author Florian @date 21/02 - 2/03
*********************************************/
Model::Model(float w, float h, const std::chrono::system_clock::time_point beginTime)  :
    m_width(w), m_height(h), m_difficulty{NORMAL_DIFFICULTY},
    m_dataBase{nullptr}, m_programBeginningTime{beginTime}
{
    m_introState = true;
    m_menuState = false;
    m_gameState = false;
    m_resetGameState = false;
}

/********************************************
    Copy Constructor
*********************************************
    @author Arthur  @date 14/04 - 6/05
*********************************************/
Model::Model(const Model& model) :
    m_width(model.m_width), m_height(model.m_height), m_difficulty{model.m_difficulty},m_dataBase{model.m_dataBase},
    m_programBeginningTime{model.m_programBeginningTime}, m_introState{model.m_introState},
    m_menuState{model.m_menuState}, m_gameState{model.m_gameState}, m_resetGameState{model.m_resetGameState}
{ }

/********************************************
    Destructor
*********************************************
    @author Arthur  @date 21/02 - 26/03
    @author Florian @date 21/02 - 2/03
*********************************************/
Model::~Model()
{ }


/********************************************
    Getters
*********************************************
    @author Arthur  @date 21/02 - 2/05
    @author Florian @date 21/02 - 25/02
*********************************************/
DataBase *Model::getDataBase() const {return m_dataBase;}
int Model::getDifficulty() const {return m_difficulty;}
bool Model::getIntroState() const {return m_introState;}
bool Model::getMenuState() const {return m_menuState;}
bool Model::getGameState() const {return m_gameState;}
bool Model::getResetGameState() const {return m_resetGameState;}
chrono::system_clock::time_point Model::getProgramBeginningTime() const { return m_programBeginningTime; }


/********************************************
    Setters
*********************************************
    @author Arthur  @date 8/03 - 6/05
*********************************************/
void Model::setDataBase(DataBase *data) {m_dataBase = data;}
void Model::setDifficulty(int difficulty) {m_difficulty = difficulty;}
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
