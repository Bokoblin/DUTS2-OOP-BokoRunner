#include "../header/MenuModel.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 14/04 - 20/05
*********************************************/
MenuModel::MenuModel(const Model& model) :
    Model(model), m_homeState{true}, m_settingsState{false},
    m_leaderboardState{false}, m_shopState{false}
{
    m_settings = nullptr;
    m_shop = nullptr;
    m_leaderboard = new Leaderboard;
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 14/04 - 20/05
*********************************************/
MenuModel::~MenuModel()
{
    delete m_leaderboard;
    delete m_settings;
    delete m_shop;
}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 14/04 - 16/05
*********************************************/
bool MenuModel::getHomeState() const { return m_homeState; }
//bool& MenuModel::getHomeState() { return m_homeState; }
bool MenuModel::getSettingsState() const{ return m_settingsState;}
bool MenuModel::getLeaderboardState() const{ return m_leaderboardState;}
bool MenuModel::getShopState() const { return m_shopState; }
//bool& MenuModel::getShopState() { return m_shopState; }
Leaderboard* MenuModel::getLeaderboard() const{ return m_leaderboard;}


/********************************************
    Setters
*********************************************
    @author Arthur  @date 14/04 - 14/05
*********************************************/
void MenuModel::setHomeState(bool state){ m_homeState = state;}
void MenuModel::setSettingsState(bool state){ m_settingsState = state;}
void MenuModel::setLeaderboardState(bool state){ m_leaderboardState = state;}
void MenuModel::setShopState(bool state){ m_shopState = state;}


/********************************************
    Next Step
*********************************************
    @author Arthur  @date 14/04 - 20/05
*********************************************/
void MenuModel::nextStep()
{
    //=== Delete shop if not anymore in shopState

    if ( m_shopState == false && m_shop != nullptr)
    {
        delete m_shop;
        m_shop = nullptr;
    }

    //=== Delete settings if not anymore in shopState

    if ( m_settingsState == false && m_settings != nullptr)
    {
        delete m_settings;
        m_settings = nullptr;
    }
}

/********************************************
    Launch shop function
*********************************************
    @author Arthur  @date 14/05
*********************************************/
Shop* MenuModel::launchShop()
{
    m_homeState = false;
    m_shopState = true;

    m_shop = new Shop(m_dataBase);

    return m_shop;
}

/********************************************
    Launch settings function
*********************************************
    @author Arthur  @date 20/05
*********************************************/
Settings* MenuModel::launchSettings()
{
    m_homeState = false;
    m_settingsState = true;

    m_settings = new Settings(m_dataBase);

    return m_settings;
}
