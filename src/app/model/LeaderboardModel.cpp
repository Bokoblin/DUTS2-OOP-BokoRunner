#include "LeaderboardModel.h"

/**
 * Constructs a Leaderboard model with database
 * @author Arthur
 * @date 19/04/16 - 29/01/17
 *
 * @param dataBase the common app's dataBase
 */
LeaderboardModel::LeaderboardModel(DataBase *dataBase) :
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
LeaderboardModel::~LeaderboardModel() = default;


/**
 * Next Step
 * @author Arthur
 * @date 29/01/17
 */
void LeaderboardModel::nextStep()
{}


/**
 * Quits leaderboard by saving configuration
 *
 * @author Arthur
 * @date 03/11/17
 */
void LeaderboardModel::quit()
{
    m_dataBase->pushConfigurationToFile();
}

