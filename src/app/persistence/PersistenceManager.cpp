#include "PersistenceManager.h"
#include "app/model/utils/StringHash.h"

using std::string;
using std::to_string;
using std::stoi;
using pugi::xml_document;
using pugi::xml_node;
using pugi::xml_attribute;
using Bokoblin::SimpleLogger::Logger;

//------------------------------------------------
//          STATIC MEMBERS
//------------------------------------------------

bool PersistenceManager::m_isInit = false;
AppCore* PersistenceManager::m_appCore = nullptr;
xml_document PersistenceManager::m_doc;

//------------------------------------------------
//          PUBLIC METHODS
//------------------------------------------------

/**
 * Inits the app persistence manager context
 * and the persistence system
 *
 * @author Arthur
 * @date 04/02/17
 */
void PersistenceManager::initContext(AppCore* appCore)
{
    m_appCore = appCore;
    m_isInit = true;

    initPersistence();
}


/**
 * Closes the persistence manager context
 *
 * @author Arthur
 * @date 04/02/17
 */
void PersistenceManager::closeContext()
{
    m_isInit = false;
    m_appCore = nullptr;
}


/**
 * Inits the app persistence system
 * by checking existence and creating otherwise
 *
 * @author Arthur
 * @date 04/02/17
 */
void PersistenceManager::initPersistence()
{
    if (XMLHelper::loadXMLFile(m_doc, CONFIG_FILE)) {
        Logger::printInfoOnConsole("Persistence context loaded successfully");
    } else {
        Logger::printErrorOnConsole("Persistence context loading failure");
        createConfigFile();
    }
}


/**
 * Checks if persistence context is valid,
 * takes the necessary measures otherwise
 *
 * @author Arthur
 * @date 04/02/17
 */
void PersistenceManager::checkContext()
{
    if (m_isInit && m_appCore != nullptr && checkConfigFileIntegrity()) {
        Logger::printInfoOnConsole("Persistence context verified");
    } else {
        Logger::printErrorOnConsole("Persistence context check failed, please init it first...");
        throw PersistenceException();
    }
}


/**
 * Fetches the activated items
 * from persistence system
 *
 * @author Arthur
 * @date 04/02/18 - 11/02/18
 */
void PersistenceManager::fetchActivatedBonus()
{
    try {
        PersistenceManager::checkContext();

        if (fetchActivatedBonusFromConfigFile()) {
            Logger::printInfoOnConsole("Activated bonus successfully fetched");
        } else {
            Logger::printErrorOnConsole("Activated bonus fetching failure");
        }
    } catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence checking failure"));
    }
}


/**
 * Fetches the app configuration
 * from persistence system
 *
 * @author Arthur
 * @date 04/02/18 - 11/02/18
 */
void PersistenceManager::fetchConfiguration()
{
    try {
        PersistenceManager::checkContext();

        if (fetchConfigurationFromConfigFile()) {
            Logger::printInfoOnConsole("Configuration successfully fetched");
        } else {
            Logger::printErrorOnConsole("Configuration fetching failure");
        }
    } catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence checking failure"));
    }
}


/**
 * Fetches the leaderboard
 * from persistence system
 *
 * @author Arthur
 * @date 04/02/18 - 11/02/18
 */
void PersistenceManager::fetchLeaderboard()
{
    try {
        PersistenceManager::checkContext();

        if (fetchLeaderboardFromConfigFile()) {
            Logger::printInfoOnConsole("Leaderboard successfully fetched");
        } else {
            Logger::printErrorOnConsole("Leaderboard fetching failure");
        }
    } catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence checking failure"));
    }
}


/**
 * Updates the app configuration
 * of the persistence system
 *
 * @author Arthur
 * @date 04/02/18 - 11/02/18
 */
void PersistenceManager::updatePersistence()
{
    try {
        PersistenceManager::checkContext();

        if (persistConfigurationToConfigFile()) {
            Logger::printInfoOnConsole("Configuration successfully persisted");
        } else {
            Logger::printErrorOnConsole("Configuration persistence failure");
        }
    } catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence checking failure"));
    }
}


/**
 * Deletes the persistence context.
 * Does nothing
 *
 * @author Arthur
 * @date 04/02/17
 */
void PersistenceManager::deletePersistence()
{
    remove(CONFIG_FILE.c_str());
}


//------------------------------------------------
//          PRIVATE METHODS
//------------------------------------------------

/**
 * (Re)creates config file
 *
 * @author Arthur
 * @date 02/05/16 - 22/01/18
 */
void PersistenceManager::createConfigFile()
{
    XMLHelper::createXMLFile(CONFIG_FILE, DEFAULT_CONFIG_CONTENT);
    Logger::printInfoOnConsole("Configuration file successfully created");
}


/**
 * Checks if config file has been corrupted
 * by verifying file number of lines, number of each item
 *
 * @return a boolean indicating if file is corrupted
 *
 * @author Arthur
 * @date 02/05/16 - 25/01/17
 */
bool PersistenceManager::checkConfigFileIntegrity()
{
    //TODO : NON-TRIVIAL REWRITE with new structure
    //see: https://pugixml.org/docs/manual.html#loading.errors in XMLHelper
    std::fstream f;
    string line;

    f.open(CONFIG_FILE.c_str(), std::ios::in);

    //=== Opening test
    if (f.fail()) {
        return false;
    }

    //=== Count lines / elements test
    bool isPresentConfig = false; //should be true
    bool isPresentStats = false; //should be true
    bool isPresentShop = false; //should be true
    bool isPresentScoreEasy = false; //should be true
    bool isPresentScoreHard = false; //should be true
    int nbLines = 0; //should be 52 or 53
    int nbConfigChildren = 0; //should be 6
    int nbStatsChildren = 0; //should be 7
    int nbShopChildren = 0; //should be 6
    int nbScoreChildren = 0; //should be 20

    do {
        getline(f, line, '\n');
        nbLines++;

        isPresentConfig = line.find("<config>") != string::npos ? true : isPresentConfig;
        isPresentStats = line.find("<stats>") != string::npos ? true : isPresentStats;
        isPresentShop = line.find("<shop>") != string::npos ? true : isPresentShop;
        isPresentScoreEasy = line.find("<scoresEasy>") != string::npos ? true : isPresentScoreEasy;
        isPresentScoreHard = line.find("<scoresHard>") != string::npos ? true : isPresentScoreHard;

        nbConfigChildren = line.find("<configItem") != string::npos ? nbConfigChildren + 1 : nbConfigChildren;
        nbStatsChildren = line.find("<statItem") != string::npos ? nbStatsChildren + 1 : nbStatsChildren;
        nbShopChildren = line.find("<shopItem") != string::npos ? nbShopChildren + 1 : nbShopChildren;
        nbScoreChildren = line.find("<scoreItem") != string::npos ? nbScoreChildren + 1 : nbScoreChildren;
    } while (!f.eof());

    return isPresentConfig && isPresentStats && isPresentShop && isPresentScoreEasy && isPresentScoreHard
            && nbConfigChildren == 6 && nbStatsChildren == 7 && nbShopChildren == 6 && nbScoreChildren == 20
            && (nbLines == 52 || nbLines == 53);
}


/**
 * Updates variable values from file
 *
 * @author Arthur
 * @date 24/10/16 - 26/01/18
 */
bool PersistenceManager::fetchConfigurationFromConfigFile()
{
    try {
        PersistenceManager::checkContext();

        xml_node config = m_doc.child("runner").child("config");
        xml_node stats = m_doc.child("runner").child("stats");

        for (xml_node configItem: config.children("configItem")) {
            string nodeKey = string(configItem.attribute("name").value());
            xml_attribute nodeValue = configItem.attribute("value");

            switch (hash(nodeKey)) {
                case hash("language"):
                    m_appCore->m_currentLanguage = XMLHelper::safeRetrieveXMLValue<string>
                            (nodeValue, "en|fr|es", ENGLISH);
                    break;
                case hash("difficulty"):
                    m_appCore->m_currentDifficulty = XMLHelper::safeRetrieveXMLValue<int>
                            (nodeValue, "1|2", Difficulty::HARD);
                    break;
                case hash("ball_skin"):
                    m_appCore->m_currentBallSkin = XMLHelper::safeRetrieveXMLValue<string>
                            (nodeValue, "default|morphing|capsule", "default");
                    break;
                case hash("wallet"):
                    m_appCore->m_currentBallSkin = XMLHelper::safeRetrieveXMLValue<string>
                            (nodeValue, "default|morphing|capsule", "default");
                    break;
                case hash("menu_music"):
                    m_appCore->m_isMenuMusicEnabled = XMLHelper::safeRetrieveXMLValue<bool>
                            (nodeValue, BOOLEAN_REGEX, false);
                    break;
                case hash("game_music"):
                    m_appCore->m_isGameMusicEnabled = XMLHelper::safeRetrieveXMLValue<bool>
                            (nodeValue, BOOLEAN_REGEX, false);
                    break;
                default:
                    break;
            }
        }

        for (xml_node statItem: stats.children("statItem")) {
            string nodeKey = string(statItem.attribute("name").value());
            xml_attribute nodeValue = statItem.attribute("value");

            switch (hash(nodeKey)) {
                case hash("total_coins_collected"):
                    m_appCore->m_totalCoinsCollected = XMLHelper::safeRetrieveXMLValue<unsigned int>
                            (nodeValue, INTEGER_REGEX, 0);
                    break;
                case hash("total_distance_travelled"):
                    m_appCore->m_totalDistance = XMLHelper::safeRetrieveXMLValue<unsigned int>
                            (nodeValue, INTEGER_REGEX, 0);
                    break;
                case hash("total_enemies_destroyed"):
                    m_appCore->m_totalFlattenedEnemies = XMLHelper::safeRetrieveXMLValue<unsigned int>
                            (nodeValue, INTEGER_REGEX, 0);
                    break;
                case hash("per_game_coins_collected"):
                    m_appCore->m_perGameCoinsCollected = XMLHelper::safeRetrieveXMLValue<unsigned int>
                            (nodeValue, INTEGER_REGEX, 0);
                    break;
                case hash("per_game_distance_travelled"):
                    m_appCore->m_perGameDistance = XMLHelper::safeRetrieveXMLValue<unsigned int>
                            (nodeValue, INTEGER_REGEX, 0);
                    break;
                case hash("per_game_enemies_destroyed"):
                    m_appCore->m_perGameFlattenedEnemies = XMLHelper::safeRetrieveXMLValue<unsigned int>
                            (nodeValue, INTEGER_REGEX, 0);
                    break;
                case hash("total_games_played"):
                    m_appCore->m_totalGamesPlayed = XMLHelper::safeRetrieveXMLValue<unsigned int>
                            (nodeValue, INTEGER_REGEX, 0);
                    break;
                default:
                    break;
            }
        }
        return true;
    } catch (PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence checking failure"));
        return false;
    }
}


/**
 * Updates each score array
 * with values from config file
 *
 * @author Arthur
 * @date 23/10/16 - 26/01/18
 */
bool PersistenceManager::fetchLeaderboardFromConfigFile()
{
    try {
        PersistenceManager::checkContext();

        xml_node scoresEasy = m_doc.child("runner").child("scoresEasy");
        xml_node scoresHard = m_doc.child("runner").child("scoresHard");

        m_appCore->m_scoresEasyArray.clear();
        m_appCore->m_scoresHardArray.clear();

        for (xml_node scoreItem: scoresEasy.children("scoreItem")) {
            if (string(scoreItem.attribute("value").value()) != "0") {
                m_appCore->m_scoresEasyArray.insert(XMLHelper::safeRetrieveXMLValue<unsigned int>
                                                            (scoreItem.attribute("value"), INTEGER_REGEX, 0));
            }
        }
        for (xml_node scoreItem: scoresHard.children("scoreItem")) {
            if (string(scoreItem.attribute("value").value()) != "0") {
                m_appCore->m_scoresHardArray.insert(XMLHelper::safeRetrieveXMLValue<unsigned int>
                                                            (scoreItem.attribute("value"), INTEGER_REGEX, 0));
            }
        }
        return true;
    } catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence checking failure"));
        return false;
    }
}


/**
 * Updates activated items array
 *
 * @author Arthur
 * @date 14/05/16 - 26/01/18
 */
bool PersistenceManager::fetchActivatedBonusFromConfigFile()
{
    try {
        PersistenceManager::checkContext();

        xml_node shop = m_doc.child("runner").child("shop");

        for (xml_node shopItem: shop.children("shopItem")) {
            if (string(shopItem.attribute("bought").value()) == "true") {
                const string ITEM_REGEX = "shop_[a-z]+[_]{0,1}[a-z]+";
                m_appCore->m_activatedItemsArray.insert(XMLHelper::safeRetrieveXMLValue<string>
                                                                (shopItem.attribute("id"), ITEM_REGEX, ""));
            }
        }
        return true;
    } catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence checking failure"));
        return false;
    }
}


/**
 * Pushes Configuration data to file
 *
 * @author Arthur
 * @date 02/05/16 - 26/01/18
 */
bool PersistenceManager::persistConfigurationToConfigFile()
{
    try {
        PersistenceManager::checkContext();

        xml_node config = m_doc.child("runner").child("config");
        xml_node stats = m_doc.child("runner").child("stats");
        xml_node shop = m_doc.child("runner").child("shop");
        xml_node scoresEasy = m_doc.child("runner").child("scoresEasy");
        xml_node scoresHard = m_doc.child("runner").child("scoresHard");

        //=== Save configuration

        for (xml_node configItem: config.children("configItem")) {
            string nodeKey = string(configItem.attribute("name").value());
            xml_attribute nodeValue = configItem.attribute("value");

            switch (hash(nodeKey)) {
                case hash("language"):
                    nodeValue.set_value(m_appCore->m_currentLanguage.c_str());
                    break;
                case hash("difficulty"):
                    nodeValue.set_value(to_string(m_appCore->m_currentDifficulty).c_str());
                    break;
                case hash("ball_skin"):
                    nodeValue.set_value(m_appCore->m_currentBallSkin.c_str());
                    break;
                case hash("wallet"):
                    nodeValue.set_value(to_string(m_appCore->m_wallet).c_str());
                    break;
                case hash("menu_music"):
                    nodeValue.set_value(m_appCore->m_isMenuMusicEnabled);
                    break;
                case hash("game_music"):
                    nodeValue.set_value(m_appCore->m_isGameMusicEnabled);
                    break;
                default:
                    break;
            }
        }

        //=== Save stats

        for (xml_node statItem: stats.children("statItem")) {
            string nodeKey = string(statItem.attribute("name").value());
            xml_attribute nodeValue = statItem.attribute("value");

            switch (hash(nodeKey)) {
                case hash("total_coins_collected"):
                    nodeValue.set_value(to_string(m_appCore->m_totalCoinsCollected).c_str());
                    break;
                case hash("total_distance_travelled"):
                    nodeValue.set_value(to_string(m_appCore->m_totalDistance).c_str());
                    break;
                case hash("total_enemies_destroyed"):
                    nodeValue.set_value(to_string(m_appCore->m_totalFlattenedEnemies).c_str());
                    break;
                case hash("per_game_coins_collected"):
                    nodeValue.set_value(to_string(m_appCore->m_perGameCoinsCollected).c_str());
                    break;
                case hash("per_game_distance_travelled"):
                    nodeValue.set_value(to_string(m_appCore->m_perGameDistance).c_str());
                    break;
                case hash("per_game_enemies_destroyed"):
                    nodeValue.set_value(to_string(m_appCore->m_perGameFlattenedEnemies).c_str());
                    break;
                case hash("total_games_played"):
                    nodeValue.set_value(to_string(m_appCore->m_totalGamesPlayed).c_str());
                    break;
                default:
                    break;
            }
        }

        //=== Save shop activated items

        for (xml_node shopItem: shop.children("shopItem")) {
            if (m_appCore->findActivatedItem(string(shopItem.attribute("id").value()))) {
                shopItem.attribute("bought").set_value(true);
            }
        }

        //=== Save leaderboard

        auto it = m_appCore->m_scoresEasyArray.begin();
        for (xml_node scoreItem: scoresEasy.children("scoreItem")) {
            xml_attribute nodeValue = scoreItem.attribute("value");
            if (it != m_appCore->m_scoresEasyArray.end()) {
                nodeValue.set_value(to_string(*it).c_str());
                ++it;
            } else {
                nodeValue.set_value("0");
            }
        }

        it = m_appCore->m_scoresHardArray.begin();
        for (xml_node scoreItem: scoresHard.children("scoreItem")) {
            xml_attribute nodeValue = scoreItem.attribute("value");
            if (it != m_appCore->m_scoresHardArray.end()) {
                nodeValue.set_value(to_string(*it).c_str());
                ++it;
            } else {
                nodeValue.set_value("0");
            }
        }

        return m_doc.save_file(CONFIG_FILE.c_str());
    } catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence checking failure"));
        return false;
    }
}
