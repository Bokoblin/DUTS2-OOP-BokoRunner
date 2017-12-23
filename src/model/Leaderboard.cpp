#include "Leaderboard.h"

using namespace std;

/**
 * Constructs a Leaderboard model with database
 * @author Arthur
 * @date 19/04/16 - 29/01/17
 *
 * @param dataBase the common app's dataBase
 */
Leaderboard::Leaderboard(DataBase *dataBase) :
        AbstractModel(dataBase)
{
    if (!m_dataBase->checkConfigFileIntegrity())
    {
        m_dataBase->createConfigFile();
        m_dataBase->fetchConfigurationFromFile();
    }
}


/**
 * Destructor
 * @author Arthur
 * @date 19/04/16
 */
Leaderboard::~Leaderboard() = default;


/**
 * Next Step
 * @author Arthur
 * @date 29/01/17
 */
void Leaderboard::nextStep()
{}


/**
 * Quits leaderboard by saving configuration
 *
 * @author Arthur
 * @date 03/11/17
 */
void Leaderboard::quit()
{
    m_dataBase->pushConfigurationToFile();
}

