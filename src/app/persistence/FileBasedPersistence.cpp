#include "FileBasedPersistence.h"

using std::string;
using std::to_string;
using pugi::xml_document;
using pugi::xml_node;
using pugi::xml_attribute;
using Bokoblin::SimpleLogger::Logger;
using Bokoblin::XMLUtils::XMLHelper;
namespace ModelResources = Bokoblin::BokoRunner::Resources::Model;

//------------------------------------------------
//          STATIC MEMBERS
//------------------------------------------------

AppCore* FileBasedPersistence::m_appCore = nullptr;
xml_document FileBasedPersistence::m_doc;


//------------------------------------------------
//          GETTERS
//------------------------------------------------

bool FileBasedPersistence::isAppCoreInitialized() { return m_appCore != nullptr; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void FileBasedPersistence::setAppCore(AppCore* appCore) { m_appCore = appCore; }

//------------------------------------------------
//          PUBLIC METHODS
//------------------------------------------------

/**
 * @brief Creates the config file if it doesn't exit
 *
 * @author Arthur
 * @date 02/05/16 - 17/07/18
 */
bool FileBasedPersistence::createConfigFile()
{
    nullSafeGuard();

    bool success = false;
    if (XMLHelper::checkXMLFileExistence(m_appCore->getPersistenceContext())) {
        Logger::printWarning("Configuration file already exists, aborting...");
    } else if (XMLHelper::createXMLFile(m_appCore->getPersistenceContext(), generateDefaultStringConfig())) {
        Logger::printInfo("Configuration file successfully created");
        success = true;
    } else {
        Logger::printError("Configuration file creation failure");
    }

    return success;
}


/**
 * @brief Load the config file into an xml object
 *
 * @author Arthur
 * @date 25/08/18
 */
bool FileBasedPersistence::loadConfigFile()
{
    nullSafeGuard();
    return XMLHelper::loadXMLFile(m_doc, m_appCore->getPersistenceContext());
}


/**
 * @brief Remove the config file
 *
 * @author Arthur
 * @date 25/08/18
 */
bool FileBasedPersistence::removeConfigFile()
{
    nullSafeGuard();
    return XMLHelper::removeXMLFile(m_appCore->getPersistenceContext());
}


/**
 * @brief Checks a stream integrity
 * @details Checks if a stream is corrupted
 * by verifying number of lines, number of each item
 *
 * @return a boolean indicating if file is corrupted
 *
 * @author Arthur
 * @date 02/05/16 - 22/07/18
 */
bool FileBasedPersistence::checkStreamIntegrity(std::istream& stream)
{
    string content;
    string line;

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
        getline(stream, line, '\n');
        content.append(line);
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
    } while (!stream.eof());

    //To overcome the limitation of "stream" being emptied by XMLHelper::checkXMLStreamIntegrity()
    std::stringstream ss;
    ss << content.c_str();
    if (!XMLHelper::checkXMLStreamIntegrity(ss)) {
        return false;
    }

    return isPresentConfig && isPresentStats && isPresentShop && isPresentScoreEasy && isPresentScoreHard
            && nbConfigChildren == 6 && nbStatsChildren == 7 && nbShopChildren == 6 && nbScoreChildren == 20;
}


/**
 * @brief Checks config file integrity
 *
 * @return a boolean indicating if file is corrupted
 *
 * @author Arthur
 * @date 02/05/16 - 17/07/18
 */
bool FileBasedPersistence::checkStreamIntegrityFromConfigFile()
{
    nullSafeGuard();

    std::fstream f;
    f.open(m_appCore->getPersistenceContext().c_str(), std::ios::in);

    if (!f.fail()) {
        return checkStreamIntegrity(f);
    } else {
        return false;
    }
}


/**
 * @brief Checks XML document integrity
 *
 * @return a boolean indicating if file is corrupted
 *
 * @author Arthur
 * @date 17/07/2018
 */
bool FileBasedPersistence::checkStreamIntegrityFromXMLDocument()
{
    std::stringstream stream;
    m_doc.save(stream);

    return checkStreamIntegrity(stream);
}


/**
 * @brief Updates configuration values from file
 *
 * @author Arthur
 * @date 24/10/16 - 26/01/18
 */
bool FileBasedPersistence::fetchConfigurationFromConfigFile()
{
    nullSafeGuard();

    xml_node config = m_doc.child("runner").child("config");

    for (xml_node configItem: config.children("configItem")) {
        string nodeKey = string(configItem.attribute("name").value());
        xml_attribute nodeValue = configItem.attribute("value");

        switch (hash(nodeKey)) {
            case hash("language"):
                m_appCore->m_currentLanguage = XMLHelper::safeRetrieveXMLValue<string>
                        (nodeValue, "en|fr|es", ModelResources::ENGLISH);
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
                m_appCore->m_wallet = XMLHelper::safeRetrieveXMLValue<int>
                        (nodeValue, ModelResources::INTEGER_REGEX, 0);
                break;
            case hash("menu_music"):
                m_appCore->m_isMenuMusicEnabled = XMLHelper::safeRetrieveXMLValue<bool>
                        (nodeValue, ModelResources::BOOLEAN_REGEX, false);
                break;
            case hash("game_music"):
                m_appCore->m_isGameMusicEnabled = XMLHelper::safeRetrieveXMLValue<bool>
                        (nodeValue, ModelResources::BOOLEAN_REGEX, false);
                break;
            default:
                break;
        }
    }

    return true;
}


/**
 * @brief Updates statistics values from file
 *
 * @author Arthur
 * @date 24/10/16 - 25/09/18
 */
bool FileBasedPersistence::fetchStatisticsFromConfigFile()
{
    nullSafeGuard();

    xml_node stats = m_doc.child("runner").child("stats");

    for (xml_node statItem: stats.children("statItem")) {
        string nodeKey = string(statItem.attribute("name").value());
        xml_attribute nodeValue = statItem.attribute("value");
        m_appCore->m_statsMap[nodeKey] =
                XMLHelper::safeRetrieveXMLValue<unsigned int>(nodeValue, ModelResources::INTEGER_REGEX, 0);
    }

    return true;
}


/**
 * @brief Updates each score array
 * with values from config file
 *
 * @author Arthur
 * @date 23/10/16 - 25/09/18
 */
bool FileBasedPersistence::fetchLeaderboardFromConfigFile()
{
    nullSafeGuard();

    xml_node scoresEasy = m_doc.child("runner").child("scoresEasy");
    xml_node scoresHard = m_doc.child("runner").child("scoresHard");

    m_appCore->m_scoresEasyArray.clear();
    m_appCore->m_scoresHardArray.clear();

    for (xml_node scoreItem: scoresEasy.children("scoreItem")) {
        insertScore(m_appCore->m_scoresEasyArray, scoreItem);
    }
    for (xml_node scoreItem: scoresHard.children("scoreItem")) {
        insertScore(m_appCore->m_scoresHardArray, scoreItem);
    }

    return true;
}


/**
 * @brief Updates activated items array
 * with values from config file
 *
 * @author Arthur
 * @date 14/05/16 - 26/01/18
 */
bool FileBasedPersistence::fetchActivatedBonusFromConfigFile()
{
    nullSafeGuard();

    xml_node shop = m_doc.child("runner").child("shop");

    for (xml_node shopItem: shop.children("shopItem")) {
        if (string(shopItem.attribute("bought").value()) == "true") {
            const string ITEM_REGEX = "shop_[a-z]+[_]{0,1}[a-z]+";
            m_appCore->m_activatedItemsArray.insert(XMLHelper::safeRetrieveXMLValue<string>
                                                            (shopItem.attribute("id"), ITEM_REGEX, ""));
        }
    }
    return true;
}


/**
 * @brief Updates shop items array
 * with values from config file
 *
 * @author Arthur
 * @date 13/10/18
 */
bool FileBasedPersistence::fetchShopItemsFromConfigFile()
{
    nullSafeGuard();

    xml_node shop = m_doc.child("runner").child("shop");

    for (pugi::xml_node shopItem: shop.children("shopItem")) {
        //Updates item's attributes
        string id = shopItem.attribute("id").value();
        string name = LocalizationManager::fetchLocalizedString(id + "_name");
        string desc = LocalizationManager::fetchLocalizedString(id + "_desc");
        int price = std::stoi(shopItem.attribute("price").value());
        bool isBought = ((string) shopItem.attribute("bought").value()) == "true";

        //Adds item to array
        m_appCore->m_shopItemsArray.push_back(new ShopItem(id, name, desc, price, isBought));
    }
    return true;
}


/**
 * @brief Pushes Configuration data to file
 *
 * @author Arthur
 * @date 02/05/16 - 25/09/18
 */
bool FileBasedPersistence::persistConfigurationToConfigFile()
{
    nullSafeGuard();

    xml_node config = m_doc.child("runner").child("config");
    xml_node stats = m_doc.child("runner").child("stats");
    xml_node shop = m_doc.child("runner").child("shop");

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
        statItem.attribute("value").set_value(to_string(m_appCore->m_statsMap[nodeKey]).c_str());
    }

    //=== Save shop activated items

    for (xml_node shopItem: shop.children("shopItem")) {
        if (m_appCore->findActivatedItem(string(shopItem.attribute("id").value()))) {
            shopItem.attribute("bought").set_value(true);
        }
    }

    //=== Save leaderboard

    saveScores(m_appCore->m_scoresEasyArray, m_doc.child("runner").child("scoresEasy"));
    saveScores(m_appCore->m_scoresHardArray, m_doc.child("runner").child("scoresHard"));

    return m_doc.save_file(m_appCore->getPersistenceContext().c_str());
}

//------------------------------------------------
//          PRIVATE METHODS
//------------------------------------------------

/**
 * @brief Checks if the app core is initialized.
 * Takes appropriate actions otherwise.
 *
 * @author Arthur
 * @date 25/08/18
 */
void FileBasedPersistence::nullSafeGuard()
{
    if (m_appCore == nullptr) {
        Logger::printError("Illegal usage of FileBasedPersistence class");
        exit(EXIT_FAILURE);
    }
}


/**
 * @brief Insert a score into an array,
 * or a default value if the score is invalid
 *
 * @author Arthur
 * @date 25/09/18
 */
void FileBasedPersistence::insertScore(std::set<int>& array, const xml_node& scoreItem)
{
    if (string(scoreItem.attribute("value").value()) != "0") {
        array.insert(XMLHelper::safeRetrieveXMLValue<unsigned int>
                             (scoreItem.attribute("value"), ModelResources::INTEGER_REGEX, 0));
    }
}


/**
 * @brief Save all scores of an array into an xml node
 *
 * @author Arthur
 * @date 25/09/18
 */
void FileBasedPersistence::saveScores(const std::set<int>& array, const xml_node& scoreNode)
{
    auto it = array.begin();
    for (xml_node scoreItem: scoreNode.children("scoreItem")) {
        xml_attribute nodeValue = scoreItem.attribute("value");
        if (it != array.end()) {
            nodeValue.set_value(to_string(*it).c_str());
            ++it;
        } else {
            nodeValue.set_value("0");
        }
    }
}

//TODO [2.0.x] Generate xml_document programmatically instead of having a giant string
//  That would allow a minimum file, especially for scores
string FileBasedPersistence::generateDefaultStringConfig()
{
    return "<?xml version=\"1.0\"?>\n"
           "<runner>\n"
           "\t<config>\n"
           "\t\t<configItem type=\"string\" name=\"language\" value=\"en\"/>\n"
           "\t\t<configItem type=\"int\" name=\"difficulty\" value=\"2\"/>\n"
           "\t\t<configItem type=\"string\" name=\"ball_skin\" value=\"default\"/>\n"
           "\t\t<configItem type=\"unsigned int\" name=\"wallet\" value=\"0\"/>\n"
           "\t\t<configItem type=\"boolean\" name=\"menu_music\" value=\"false\"/>\n"
           "\t\t<configItem type=\"boolean\" name=\"game_music\" value=\"true\"/>\n"
           "\t</config>\n"
           "\t<stats>\n"
           "\t\t<statItem type=\"unsigned int\" name=\"total_distance_travelled\" value=\"0\"/>\n"
           "\t\t<statItem type=\"unsigned int\" name=\"total_enemies_destroyed\" value=\"0\"/>\n"
           "\t\t<statItem type=\"unsigned int\" name=\"total_coins_collected\" value=\"0\"/>\n"
           "\t\t<statItem type=\"unsigned int\" name=\"total_games_played\" value=\"0\"/>\n"
           "\t\t<statItem type=\"unsigned int\" name=\"per_game_distance_travelled\" value=\"0\"/>\n"
           "\t\t<statItem type=\"unsigned int\" name=\"per_game_enemies_destroyed\" value=\"0\"/>\n"
           "\t\t<statItem type=\"unsigned int\" name=\"per_game_coins_collected\" value=\"0\"/>\n"
           "\t</stats>\n"
           "\t<shop>\n"
           "\t\t<shopItem type=\"boolean\" id=\"shop_doubler\" price=\"1000\" bought=\"false\"/>\n"
           "\t\t<shopItem type=\"boolean\" id=\"shop_shield_plus\" price=\"100\" bought=\"false\"/>\n"
           "\t\t<shopItem type=\"boolean\" id=\"shop_mega_plus\" price=\"200\" bought=\"false\"/>\n"
           "\t\t<shopItem type=\"boolean\" id=\"shop_fly_plus\" price=\"180\" bought=\"false\"/>\n"
           "\t\t<shopItem type=\"boolean\" id=\"shop_morphing\" price=\"500\" bought=\"false\"/>\n"
           "\t\t<shopItem type=\"boolean\" id=\"shop_capsule\" price=\"60\" bought=\"false\"/>\n"
           "\t</shop>\n"
           "\t<scoresEasy>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t</scoresEasy>\n"
           "\t<scoresHard>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t\t<scoreItem type=\"unsigned int\" value=\"0\"/>\n"
           "\t</scoresHard>\n"
           "</runner>";
}
