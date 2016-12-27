#include "MenuModel.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 14/04 - 26/12
 */
MenuModel::MenuModel(DataBase *dataBase) :
    AbstractModel(dataBase), m_menuState{HOME}
{
    m_settings = nullptr;
    m_shop = nullptr;
    m_leaderboard = nullptr;
}


/**
 * Destructor
 * @author Arthur
 * @date 14/04 - 21/05
 */
MenuModel::~MenuModel()
{
    delete m_leaderboard;
    delete m_settings;
    delete m_shop;
}


//=== Getters & Setters

MenuState MenuModel::getMenuState() const { return m_menuState; }
void MenuModel::setMenuState(MenuState state){ m_menuState = state;}


/**
 * Next Step
 * @author Arthur
 * @date 14/04 - 21/05
 */
void MenuModel::nextStep()
{
    //=== Delete leaderboard if not anymore in shopState

    if (m_menuState == LEADERBOARD)
    {
        m_leaderboard->nextStep();
    }

    if (m_menuState != LEADERBOARD && m_leaderboard != nullptr)
    {
        delete m_leaderboard;
        m_leaderboard = nullptr;
    }

    //=== Delete shop if not anymore in shopState

    if (m_menuState != SHOP && m_shop != nullptr)
    {
        delete m_shop;
        m_shop = nullptr;
    }

    //=== Delete settings if not anymore in shopState

    if (m_menuState != SETTINGS && m_settings != nullptr)
    {
        delete m_settings;
        m_settings = nullptr;
    }
}


/**
 * Launch leaderboard function
 * @author Arthur
 * @date 21/05
 */
Leaderboard* MenuModel::launchLeaderboard()
{
    m_menuState = LEADERBOARD;
    m_leaderboard = new Leaderboard(m_dataBase);
    return m_leaderboard;
}


/**
 * Launch shop function
 * @author Arthur
 * @date 14/05
 */
Shop* MenuModel::launchShop()
{
    m_menuState = SHOP;
    m_shop = new Shop(m_dataBase);
    return m_shop;
}

/**
 * Launch settings function
 * @author Arthur
 * @date 20/05
 */
Settings* MenuModel::launchSettings()
{
    m_menuState = SETTINGS;
    m_settings = new Settings(m_dataBase);
    return m_settings;
}

