#include "LeaderboardModel.h"

//------------------------------------------------
//          CONSTRUCTOR / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs a Leaderboard model with database
 * @author Arthur
 * @date 19/04/16 - 04/02/18
 *
 * @param dataBase the common app's dataBase
 */
LeaderboardModel::LeaderboardModel(DataBase *dataBase) :
        AbstractModel(dataBase)
{
    PersistenceManager::fetchLeaderboard();
}


/**
 * Destructor
 * @author Arthur
 * @date 19/04/16
 */
LeaderboardModel::~LeaderboardModel() = default;


//------------------------------------------------
//          METHODS
//------------------------------------------------

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
 * @date 03/11/17 - 04/02/18
 */
void LeaderboardModel::quit()
{
    PersistenceManager::updatePersistence();
}

