#include "../header/MenuModel.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 14/04
*********************************************/
MenuModel::MenuModel(const Model& model) :
    Model(model), m_homeState{true}, m_settingsState{false}
{}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 14/04
*********************************************/
MenuModel::~MenuModel()
{}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 14/04
*********************************************/
bool MenuModel::getHomeState() const
{
    return m_homeState;
}
bool MenuModel::getSettingsState() const
{
    return m_settingsState;
}


/********************************************
    Setters
*********************************************
    @author Arthur  @date 14/04
*********************************************/
void MenuModel::setHomeState(bool state)
{
    m_homeState = state;
}
void MenuModel::setSettingsState(bool state)
{
    m_settingsState = state;
}


/********************************************
    Next Step
*********************************************
    @author Arthur  @date 14/04
*********************************************/
void MenuModel::nextStep()
{

}

