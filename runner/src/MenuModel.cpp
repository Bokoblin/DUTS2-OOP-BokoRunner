#include "../header/MenuModel.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 14/04
*********************************************/
MenuModel::MenuModel(const Model& model) :
    Model(model), m_homeState{true}, m_settingsState{false}
{
    m_lb = new Leaderboard;
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 14/04 - 19/04
*********************************************/
MenuModel::~MenuModel()
{
    delete m_lb;
}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 14/04 - 19/04
*********************************************/
bool MenuModel::getHomeState() const { return m_homeState; }
bool MenuModel::getSettingsState() const{ return m_settingsState;}
bool MenuModel::getLeaderboardState() const{ return m_leaderboardState;}
Leaderboard* MenuModel::getLeaderboard() const{ return m_lb;}


/********************************************
    Setters
*********************************************
    @author Arthur  @date 14/04 - 19/04
*********************************************/
void MenuModel::setHomeState(bool state){ m_homeState = state;}
void MenuModel::setSettingsState(bool state){ m_settingsState = state;}
void MenuModel::setLeaderboardState(bool state){ m_leaderboardState = state;}


/********************************************
    Next Step
*********************************************
    @author Arthur  @date 14/04
*********************************************/
void MenuModel::nextStep()
{

}
