#include "PersistenceManager.h"
#include "app/model/utils/StringHash.h"

using std::string;
using Bokoblin::SimpleLogger::Logger;

//------------------------------------------------
//          STATIC MEMBERS
//------------------------------------------------

bool PersistenceManager::m_isInit = false;

//------------------------------------------------
//          GETTERS
//------------------------------------------------

bool PersistenceManager::isInit(){ return m_isInit; }

//------------------------------------------------
//          PUBLIC METHODS
//------------------------------------------------

/**
 * @brief Inits the app persistence manager context
 * and the persistence system
 *
 * @author Arthur
 * @date 04/02/18 - 25/08/2018
 */
void PersistenceManager::initContext(AppCore* appCore)
{
    FileBasedPersistence::setAppCore(appCore);
    m_isInit = true;

    initPersistence();
}


/**
 * @brief Closes the persistence manager context
 *
 * @author Arthur
 * @date 04/02/18 - 25/08/2018
 */
void PersistenceManager::closeContext()
{
    m_isInit = false;
    FileBasedPersistence::setAppCore(nullptr);
}


/**
 * @brief Inits the app persistence system
 * by checking existence and creating otherwise
 *
 * @author Arthur
 * @date 04/02/18 - 25/08/2018
 */
void PersistenceManager::initPersistence()
{
    if (FileBasedPersistence::checkStreamIntegrityFromConfigFile() && FileBasedPersistence::loadConfigFile()) {
        Logger::printInfoOnConsole("Persistence init success");
    } else {
        Logger::printWarningOnConsole("Persistence context loading failure, creating it...");
        if (FileBasedPersistence::createConfigFile()) {
            PersistenceManager::initPersistence();
        }
    }
}


/**
 * @brief Checks if persistence context is valid
 * @throws PersistenceException
 *
 * @author Arthur
 * @date 04/02/18 - 25/08/2018
 */
void PersistenceManager::checkContext() noexcept(false)
{
    if (m_isInit && FileBasedPersistence::getAppCore() != nullptr
            && FileBasedPersistence::checkStreamIntegrityFromXMLDocument()) {
        Logger::printInfoOnConsole("Persistence context verified");
    } else {
        Logger::printErrorOnConsole("Persistence context check failed, please init it first...");
        throw PersistenceException();
    }
}


/**
 * @brief Fetches the activated items
 * from persistence system
 *
 * @author Arthur
 * @date 04/02/18 - 25/08/2018
 */
void PersistenceManager::fetchActivatedBonus()
{
    try {
        PersistenceManager::checkContext();

        if (FileBasedPersistence::fetchActivatedBonusFromConfigFile()) {
            Logger::printInfoOnConsole("Activated bonus successfully fetched");
        } else {
            Logger::printErrorOnConsole("Activated bonus fetching failure");
        }
    } catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence context checking failure"));
    }
}


/**
 * @brief Fetches the app configuration
 * from persistence system
 *
 * @author Arthur
 * @date 04/02/18 - 25/08/2018
 */
void PersistenceManager::fetchConfiguration()
{
    try {
        PersistenceManager::checkContext();

        if (FileBasedPersistence::fetchConfigurationFromConfigFile()) {
            Logger::printInfoOnConsole("Configuration successfully fetched");
        } else {
            Logger::printErrorOnConsole("Configuration fetching failure");
        }
    } catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence context checking failure"));
    }
}


/**
 * @brief Fetches the app statistics
 * from persistence system
 *
 * @author Arthur
 * @date 17/07/18 - 25/08/2018
 */
void PersistenceManager::fetchStatistics()
{
    try {
        PersistenceManager::checkContext();

        if (FileBasedPersistence::fetchStatisticsFromConfigFile()) {
            Logger::printInfoOnConsole("Statistics successfully fetched");
        } else {
            Logger::printErrorOnConsole("Statistics fetching failure");
        }
    } catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence context checking failure"));
    }
}


/**
 * @brief Fetches the leaderboard
 * from persistence system
 *
 * @author Arthur
 * @date 04/02/18 - 25/08/2018
 */
void PersistenceManager::fetchLeaderboard()
{
    try {
        PersistenceManager::checkContext();

        if (FileBasedPersistence::fetchLeaderboardFromConfigFile()) {
            Logger::printInfoOnConsole("Leaderboard successfully fetched");
        } else {
            Logger::printErrorOnConsole("Leaderboard fetching failure");
        }
    } catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence context checking failure"));
    }
}


/**
 * @brief Updates the app configuration
 * of the persistence system
 *
 * @author Arthur
 * @date 04/02/18 - 25/08/18
 */
void PersistenceManager::updatePersistence()
{
    try {
        PersistenceManager::checkContext();

        if (FileBasedPersistence::persistConfigurationToConfigFile()) {
            Logger::printInfoOnConsole("Configuration successfully persisted");
        } else {
            Logger::printErrorOnConsole("Configuration persistence failure");
        }
    } catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence context checking failure"));
    }
}


/**
 * @brief Resets the persistence context.
 *
 * @author Arthur
 * @date 16/07/18 - 25/08/18
 */
void PersistenceManager::resetPersistence()
{
    if (FileBasedPersistence::removeConfigFile()
            && FileBasedPersistence::createConfigFile()
            && FileBasedPersistence::loadConfigFile()) {
        Logger::printInfoOnConsole("Persistence context successfully reset");
    } else {
        Logger::printErrorOnConsole("Persistence context reset failure");
    }
}


/**
 * @brief Deletes the persistence context
 *
 * @author Arthur
 * @date 04/02/17 - 25/08/18
 */
void PersistenceManager::deletePersistence()
{
    if (FileBasedPersistence::removeConfigFile()) {
        Logger::printInfoOnConsole("Persistence context successfully deleted");
    } else {
        Logger::printErrorOnConsole("Persistence context delete failure");
    }
}