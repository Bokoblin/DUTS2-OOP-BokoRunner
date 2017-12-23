#include "MenuModel.h"

using namespace std;

/**
 * Constructs a MenuModel with the app common model
 * @author Arthur
 * @date 14/04/16 - 29/01/17
 *
 * @param dataBase the app dataBase
 */
MenuModel::MenuModel(DataBase *dataBase) :
    AbstractModel(dataBase), m_menuState{HOME}
{
    m_commands = nullptr;
    m_settings = nullptr;
    m_shop = nullptr;
    m_leaderboard = nullptr;
}


/**
 * Destructor
 * @author Arthur
 * @date 14/04/16 - 24/01/17
 */
MenuModel::~MenuModel()
{
    delete m_commands;
    delete m_leaderboard;
    delete m_settings;
    delete m_shop;
}


//=== Getters & Setters

MenuState MenuModel::getMenuState() const { return m_menuState; }
void MenuModel::setMenuState(MenuState state){ m_menuState = state; }


/**
 * Next Step
 * @author Arthur
 * @date 14/04/16 - 24/01/17
 */
void MenuModel::nextStep()
{
    chrono::system_clock::duration currentNextStepDelay = chrono::system_clock::now() - m_lastTime;

    if (currentNextStepDelay > chrono::milliseconds(1500))
    {

        //=== Delete commands if not anymore current menu state

        if (m_menuState != COMMANDS && m_commands != nullptr)
        {
            delete m_commands;
            m_commands = nullptr;
        }

        //=== Delete leaderboard if not anymore current menu state

        if (m_menuState != LEADERBOARD && m_leaderboard != nullptr)
        {
            delete m_leaderboard;
            m_leaderboard = nullptr;
        }

        //=== Delete shop if not anymore current menu state

        if (m_menuState != SHOP && m_shop != nullptr)
        {
            delete m_shop;
            m_shop = nullptr;
        }

        //=== Delete settings if not anymore current menu state

        if (m_menuState != SETTINGS && m_settings != nullptr)
        {
            delete m_settings;
            m_settings = nullptr;
        }
    }
}


/**
 * Launches commands function
 * @author Arthur
 * @date 24/01/17
 */
Commands* MenuModel::launchCommands()
{
    m_menuState = COMMANDS;
    m_commands = new Commands(m_dataBase);
    return m_commands;
}


/**
 * Launches leaderboard function
 * @author Arthur
 * @date 21/05/16
 */
Leaderboard* MenuModel::launchLeaderboard()
{
    m_menuState = LEADERBOARD;
    m_leaderboard = new Leaderboard(m_dataBase);
    return m_leaderboard;
}


/**
 * Launches shop function
 * @author Arthur
 * @date 14/05/16
 */
Shop* MenuModel::launchShop()
{
    m_menuState = SHOP;
    m_shop = new Shop(m_dataBase);
    return m_shop;
}


/**
 * Launches settings function
 * @author Arthur
 * @date 20/05/16
 */
Settings* MenuModel::launchSettings()
{
    m_menuState = SETTINGS;
    m_settings = new Settings(m_dataBase);
    return m_settings;
}
