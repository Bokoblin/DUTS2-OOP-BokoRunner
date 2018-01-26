#include "DataBase.h"

using std::string;
using std::to_string;
using std::stoi;
using Bokoblin::SimpleLogger::Logger;

/**
 * Constructs the app's database by initializing
 * all the data from config (backup) file
 *
 * @author Arthur
 * @date 02/05/16 - 29/01/17
 */
DataBase::DataBase() :
    m_currentCoinsNumber{0}, m_currentDistance{0}, m_currentFlattenedEnemies{0},
    m_currentScore{0}, m_isMenuMusicEnabled{false}, m_isGameMusicEnabled{false},
    m_appState{SPLASH}, m_scoreBonusFlattenedEnemies{0}
{
    if (!checkConfigFileIntegrity())
        createConfigFile();
    fetchConfigurationFromFile();
}


/**
 * Destructor
 * @author Arthur
 * @date 26/11/17
 */
DataBase::~DataBase() = default;


//=== Getters

AppState DataBase::getAppState() const { return m_appState; }
int DataBase::getTotalCoinsNumber() const { return m_totalCoinsCollected; }
int DataBase::getTotalDistance() const { return m_totalDistance; }
int DataBase::getTotalFlattenedEnemies() const { return m_totalFlattenedEnemies; }
int DataBase::getTotalGamesPlayed() const { return m_totalGamesPlayed; }
int DataBase::getPerGameCoinsNumber() const { return m_perGameCoinsCollected; }
int DataBase::getPerGameDistance() const { return m_perGameDistance; }
int DataBase::getPerGameFlattenedEnemies() const { return m_perGameFlattenedEnemies; }
int DataBase::getCurrentCoinsNumber() const { return m_currentCoinsNumber; }
int DataBase::getCurrentDistance() const { return (int)m_currentDistance; }
int DataBase::getCurrentFlattenedEnemies() const { return m_currentFlattenedEnemies; }
int DataBase::getCurrentScore() const { return m_currentScore; }
int DataBase::getDifficulty() const { return m_currentDifficulty;}
int DataBase::getWallet() const { return m_wallet;}
bool DataBase::isMenuMusicEnabled() const { return m_isMenuMusicEnabled; }
bool DataBase::isGameMusicEnabled() const { return m_isGameMusicEnabled; }
bool DataBase::isScoreEasyArrayEmpty() const { return m_scoresEasyArray.empty(); }
bool DataBase::isScoreHardArrayEmpty() const { return m_scoresHardArray.empty(); }
string DataBase::getLanguage() const { return m_currentLanguage; }
string DataBase::getBallSkin() const { return m_currentBallSkin; }
string DataBase::getLanguageFile() const
{
    if (m_currentLanguage == ENGLISH)
        return ENGLISH_STRINGS;
    else if (m_currentLanguage == FRENCH)
        return FRENCH_STRINGS;
    else if (m_currentLanguage == SPANISH)
        return SPANISH_STRINGS;
    else
        return ENGLISH_STRINGS; //Default
}


//=== Setters

void DataBase::setAppState(AppState state) { m_appState = state; }
void DataBase::decreaseWallet(int amount) { m_wallet -= amount; }
void DataBase::increaseCurrentCoinsCollected(int amount) { m_currentCoinsNumber += amount; }
void DataBase::increaseCurrentDistance(float amount) { m_currentDistance += amount; }
void DataBase::increaseCurrentFlattenedEnemies(int amount)
{
    m_scoreBonusFlattenedEnemies += amount;
    m_currentFlattenedEnemies += 1;
}
void DataBase::setLanguage(const string &language) { m_currentLanguage = language; }
void DataBase::setBallSkin(const string &skin) { m_currentBallSkin = skin; }
void DataBase::setDifficulty(int difficulty) { m_currentDifficulty = difficulty; }
void DataBase::setMenuMusic(bool on) { m_isMenuMusicEnabled = on; }
void DataBase::setGameMusic(bool on) { m_isGameMusicEnabled = on; }
void DataBase::setCurrentScore(float speed)
{
    m_currentScore = (int)((speed * m_currentDistance)
                           + (COIN_MULTIPLIER * m_currentCoinsNumber)
                           + m_scoreBonusFlattenedEnemies);
}


/**
 * (Re)creates config file
 *
 * @author Arthur
 * @date 02/05/16 - 22/01/18
 */
void DataBase::createConfigFile()
{
    XMLPersistenceHelper::createXMLFile(CONFIG_FILE, DEFAULT_CONFIG_CONTENT);
}


/**
 * TODO : NON-TRIVIAL REWRITE with new structure
 *
 * Checks if config file has been corrupted
 * by verifying file number of lines, number of each item
 *
 * @return a boolean indicating if file is corrupted
 *
 * @author Arthur
 * @date 02/05/16 - 25/01/17
 */
bool DataBase::checkConfigFileIntegrity() const
{
    std::fstream f;
    string line;

    f.open(CONFIG_FILE.c_str(), std::ios::in);

    //=== Opening test
    if (f.fail())
        return false;

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

        unsigned long long int found = line.find("<config>");
        if (found != string::npos)
            isPresentConfig = true;

        found = line.find("<stats>");
        if (found != string::npos)
            isPresentStats = true;

        found = line.find("<shop>");
        if (found != string::npos)
            isPresentShop = true;

        found = line.find("<scoresEasy>");
        if (found != string::npos)
            isPresentScoreEasy = true;

        found = line.find("<scoresHard>");
        if (found != string::npos)
            isPresentScoreHard = true;

        found = line.find("<configItem");
        if (found != string::npos)
            nbConfigChildren++;

        found = line.find("<statItem");
        if (found != string::npos)
            nbStatsChildren++;

        found = line.find("<shopItem");
        if (found != string::npos)
            nbShopChildren++;

        found = line.find("<scoreItem");
        if (found != string::npos)
            nbScoreChildren++;
    } while (!f.eof());

    return isPresentConfig && isPresentStats && isPresentShop && isPresentScoreEasy && isPresentScoreHard
           && nbConfigChildren == 6 && nbStatsChildren == 7 && nbShopChildren == 6 && nbScoreChildren == 20
           && (nbLines == 52 || nbLines == 53);
}


/**
 * Fetches Configuration data from file
 *
 * @author Arthur
 * @date 02/05/16 - 24/10/16
 */
void DataBase::fetchConfigurationFromFile()
{
    fetchConfig();
    fetchScore();
    fetchActivatedShopItems();
}


/**
 * Updates variable values from file
 *
 * @author Arthur
 * @date 24/10/16 - 26/01/18
 */
void DataBase::fetchConfig()
{
    pugi::xml_document doc;
    if (XMLPersistenceHelper::loadXMLFile(doc, CONFIG_FILE))
    {
        pugi::xml_node config = doc.child("runner").child("config");
        pugi::xml_node stats = doc.child("runner").child("stats");

        for (pugi::xml_node configItem: config.children("configItem"))
        {
            if (string(configItem.attribute("name").value()) == "language")
            {
                m_currentLanguage = XMLPersistenceHelper::safeRetrieveXMLValue<string>
                        (configItem.attribute("value"), "en|fr|es", ENGLISH);
            }
            else if (string(configItem.attribute("name").value()) == "difficulty")
            {
                m_currentDifficulty = XMLPersistenceHelper::safeRetrieveXMLValue<int>
                        (configItem.attribute("value"), "1|2", HARD);
            }
            else if (string(configItem.attribute("name").value()) == "ball_skin")
            {
                m_currentBallSkin = XMLPersistenceHelper::safeRetrieveXMLValue<string>
                        (configItem.attribute("value"), "default|morphing|capsule", "default");
            }
            else if (string(configItem.attribute("name").value()) == "wallet")
            {
                m_wallet = XMLPersistenceHelper::safeRetrieveXMLValue<unsigned int>
                        (configItem.attribute("value"), "^(0|[1-9][0-9]*)$", 0);
            }
            else if (string(configItem.attribute("name").value()) == "menu_music")
            {
                m_isMenuMusicEnabled = XMLPersistenceHelper::safeRetrieveXMLValue<bool>
                        (configItem.attribute("value"), "true|false", false);
            }
            else if (string(configItem.attribute("name").value()) == "game_music")
            {
                m_isGameMusicEnabled = XMLPersistenceHelper::safeRetrieveXMLValue<bool>
                        (configItem.attribute("value"), "true|false", false);
            }
        }

        for (pugi::xml_node statItem: stats.children("statItem"))
        {
            if (string(statItem.attribute("name").value()) == "total_coins_collected")
            {
                m_totalCoinsCollected = XMLPersistenceHelper::safeRetrieveXMLValue<unsigned int>
                        (statItem.attribute("value"), "^(0|[1-9][0-9]*)$", 0);
            }
            else if (string(statItem.attribute("name").value()) == "total_distance_travelled")
            {
                m_totalDistance = XMLPersistenceHelper::safeRetrieveXMLValue<unsigned int>
                        (statItem.attribute("value"), "^(0|[1-9][0-9]*)$", 0);
            }
            else if (string(statItem.attribute("name").value()) == "total_enemies_destroyed")
            {
                m_totalFlattenedEnemies = XMLPersistenceHelper::safeRetrieveXMLValue<unsigned int>
                        (statItem.attribute("value"), "^(0|[1-9][0-9]*)$", 0);
            }
            else if (string(statItem.attribute("name").value()) == "per_game_coins_collected")
            {
                m_perGameCoinsCollected = XMLPersistenceHelper::safeRetrieveXMLValue<unsigned int>
                        (statItem.attribute("value"), "^(0|[1-9][0-9]*)$", 0);
            }
            else if (string(statItem.attribute("name").value()) == "per_game_distance_travelled")
            {
                m_perGameDistance = XMLPersistenceHelper::safeRetrieveXMLValue<unsigned int>
                        (statItem.attribute("value"), "^(0|[1-9][0-9]*)$", 0);
            }
            else if (string(statItem.attribute("name").value()) == "per_game_enemies_destroyed")
            {
                m_perGameFlattenedEnemies = XMLPersistenceHelper::safeRetrieveXMLValue<unsigned int>
                        (statItem.attribute("value"), "^(0|[1-9][0-9]*)$", 0);
            }
            else if (string(statItem.attribute("name").value()) == "total_games_played")
            {
                m_totalGamesPlayed = XMLPersistenceHelper::safeRetrieveXMLValue<unsigned int>
                        (statItem.attribute("value"), "^(0|[1-9][0-9]*)$", 0);
            }
        }
    }
    else
        Logger::printErrorOnConsole("Configuration fetching failure");
}


/**
 * Updates each score array
 * with values from config file
 *
 * @author Arthur
 * @date 23/10/16 - 26/01/18
 */
void DataBase::fetchScore()
{
    pugi::xml_document doc;
    if (XMLPersistenceHelper::loadXMLFile(doc, CONFIG_FILE))
    {
        pugi::xml_node scoresEasy = doc.child("runner").child("scoresEasy");
        pugi::xml_node scoresHard = doc.child("runner").child("scoresHard");

        m_scoresEasyArray.clear();
        m_scoresHardArray.clear();

        for (pugi::xml_node scoreItem: scoresEasy.children("scoreItem"))
        {
            if (string(scoreItem.attribute("value").value()) != "0")
            {
                m_scoresEasyArray.insert(XMLPersistenceHelper::safeRetrieveXMLValue<unsigned int>
                        (scoreItem.attribute("value"), "^(0|[1-9][0-9]*)$", 0));
            }
        }
        for (pugi::xml_node scoreItem: scoresHard.children("scoreItem"))
        {
            if (string(scoreItem.attribute("value").value()) != "0")
            {
                m_scoresHardArray.insert(XMLPersistenceHelper::safeRetrieveXMLValue<unsigned int>
                                                 (scoreItem.attribute("value"), "^(0|[1-9][0-9]*)$", 0));
            }
        }
    }
    else
        Logger::printErrorOnConsole("Score fetching failure");
}


/**
 * Updates activated items array
 *
 * @author Arthur
 * @date 14/05/16 - 26/01/18
 */
void DataBase::fetchActivatedShopItems()
{
    pugi::xml_document doc;
    if (XMLPersistenceHelper::loadXMLFile(doc, CONFIG_FILE))
    {
        pugi::xml_node shop = doc.child("runner").child("shop");

        for (pugi::xml_node shopItem: shop.children("shopItem"))
        {
            if (string(shopItem.attribute("bought").value()) == "true")
            {
                m_activatedItemsArray.insert(XMLPersistenceHelper::safeRetrieveXMLValue<string>
                                                 (shopItem.attribute("id"), "shop_[a-z|A-Z]+", ""));
            }
        }
    }
    else
        Logger::printErrorOnConsole("Activated items fetching failure");
}


/**
 * Pushes Configuration data to file
 *
 * @author Arthur
 * @date 02/05/16 - 26/01/18
 */
void DataBase::pushConfigurationToFile() const
{
    pugi::xml_document doc;
    if (XMLPersistenceHelper::loadXMLFile(doc, CONFIG_FILE))
    {
        pugi::xml_node config = doc.child("runner").child("config");
        pugi::xml_node stats = doc.child("runner").child("stats");
        pugi::xml_node scoresEasy = doc.child("runner").child("scoresEasy");
        pugi::xml_node scoresHard = doc.child("runner").child("scoresHard");

        //Save config
        for (pugi::xml_node configItem: config.children("configItem"))
        {
            if (string(configItem.attribute("name").value()) == "language")
            {
                pugi::xml_attribute nodeValue = configItem.attribute("value");
                nodeValue.set_value(m_currentLanguage.c_str());
            }
            else if (string(configItem.attribute("name").value()) == "difficulty")
            {
                pugi::xml_attribute nodeValue = configItem.attribute("value");
                nodeValue.set_value((to_string(m_currentDifficulty)).c_str());
            }
            else if (string(configItem.attribute("name").value()) == "ball_skin")
            {
                pugi::xml_attribute nodeValue = configItem.attribute("value");
                nodeValue.set_value(m_currentBallSkin.c_str());
            }
            else if (string(configItem.attribute("name").value()) == "wallet")
            {
                pugi::xml_attribute nodeValue = configItem.attribute("value");
                nodeValue.set_value((to_string(m_wallet)).c_str());
            }
            else if (string(configItem.attribute("name").value()) == "menu_music")
            {
                pugi::xml_attribute nodeValue = configItem.attribute("value");
                nodeValue.set_value(m_isMenuMusicEnabled);
            }
            else if (string(configItem.attribute("name").value()) == "game_music")
            {
                pugi::xml_attribute nodeValue = configItem.attribute("value");
                nodeValue.set_value(m_isGameMusicEnabled);
            }
        }

        //Save stats
        for (pugi::xml_node statItem: stats.children("statItem"))
        {
            if (string(statItem.attribute("name").value()) == "total_coins_collected")
            {
                pugi::xml_attribute nodeValue = statItem.attribute("value");
                nodeValue.set_value((to_string(m_totalCoinsCollected)).c_str());
            }
            else if (string(statItem.attribute("name").value()) == "total_distance_travelled")
            {
                pugi::xml_attribute nodeValue = statItem.attribute("value");
                nodeValue.set_value((to_string(m_totalDistance)).c_str());
            }
            else if (string(statItem.attribute("name").value()) == "total_enemies_destroyed")
            {
                pugi::xml_attribute nodeValue = statItem.attribute("value");
                nodeValue.set_value((to_string(m_totalFlattenedEnemies)).c_str());
            }
            else if (string(statItem.attribute("name").value()) == "per_game_coins_collected")
            {
                pugi::xml_attribute nodeValue = statItem.attribute("value");
                nodeValue.set_value((to_string(m_perGameCoinsCollected)).c_str());
            }
            else if (string(statItem.attribute("name").value()) == "per_game_distance_travelled")
            {
                pugi::xml_attribute nodeValue = statItem.attribute("value");
                nodeValue.set_value((to_string(m_perGameDistance)).c_str());
            }
            else if (string(statItem.attribute("name").value()) == "per_game_enemies_destroyed")
            {
                pugi::xml_attribute nodeValue = statItem.attribute("value");
                nodeValue.set_value((to_string(m_perGameFlattenedEnemies)).c_str());
            }
            else if (string(statItem.attribute("name").value()) == "total_games_played")
            {
                pugi::xml_attribute nodeValue = statItem.attribute("value");
                nodeValue.set_value((to_string(m_totalGamesPlayed)).c_str());
            }
        }

        //Save score
        auto it = m_scoresEasyArray.begin();
        for (pugi::xml_node scoreItem: scoresEasy.children("scoreItem"))
        {
            pugi::xml_attribute nodeValue = scoreItem.attribute("value");
            if (it != m_scoresEasyArray.end())
            {
                nodeValue.set_value((to_string(*it)).c_str());
                ++it;
            }
            else
                nodeValue.set_value("0");
        }

        it = m_scoresHardArray.begin();
        for (pugi::xml_node scoreItem: scoresHard.children("scoreItem"))
        {
            pugi::xml_attribute nodeValue = scoreItem.attribute("value");
            if (it != m_scoresHardArray.end())
            {
                nodeValue.set_value((to_string(*it)).c_str());
                ++it;
            }
            else
                nodeValue.set_value("0");
        }

        doc.save_file(CONFIG_FILE.c_str());
    }
    else
        Logger::printErrorOnConsole("Configuration pushing failure");
}


/**
 * Saves Current Game
 * @author Arthur
 * @date 02/05/16 - 14/01/17
 */
void DataBase::saveCurrentGame()
{
    //add current game values to total values
    m_totalCoinsCollected += m_currentCoinsNumber;
    m_wallet += m_currentCoinsNumber;
    m_totalDistance += (int)m_currentDistance;
    m_totalFlattenedEnemies += m_currentFlattenedEnemies;
    addNewScore(m_currentScore);

    //update per game stats if better
    if (m_currentCoinsNumber > m_perGameCoinsCollected)
        m_perGameCoinsCollected = m_currentCoinsNumber;
    if (m_currentDistance > m_perGameDistance)
        m_perGameDistance = (int)m_currentDistance;
    if (m_currentFlattenedEnemies > m_perGameFlattenedEnemies)
        m_perGameFlattenedEnemies = m_currentFlattenedEnemies;

    Logger::printInfoOnConsole("Current game saved");
}


/**
 * Adds a new score to the corresponding score array
 * @author Arthur
 * @date 23/10/16 - 23/01/17
 *
 * @param score to add to the score array
 */
void DataBase::addNewScore(int score)
{
    if (m_currentDifficulty == EASY)
    {
        m_scoresEasyArray.insert(score);
        while (m_scoresEasyArray.size() > MAX_SCORES)
            m_scoresEasyArray.erase(m_scoresEasyArray.begin());

        Logger::printInfoOnConsole("New score saved in EASY leaderboard");
    }
    else
    {
        m_scoresHardArray.insert(score);
        while (m_scoresHardArray.size() > MAX_SCORES)
            m_scoresHardArray.erase(m_scoresHardArray.begin());

        Logger::printInfoOnConsole("New score saved in HARD leaderboard");
    }
}


/**
 * Resets Current Game to create a new one
 * @author Arthur
 * @date 02/05/16
 */
void DataBase::launchNewGame()
{
    //for launching a new game
    m_totalGamesPlayed += 1;
    m_currentCoinsNumber = 0;
    m_currentDistance = 0;
    m_currentFlattenedEnemies = 0;
    m_currentScore = 0;
}


/**
 * Clears leaderboard composed of two score arrays
 * @author Arthur
 * @date 24/10/16 - 24/01/17
 */
void DataBase::clearLeaderboard()
{
    m_scoresEasyArray.clear();
    m_scoresHardArray.clear();

    if (m_scoresEasyArray.empty() && m_scoresHardArray.empty())
        Logger::printInfoOnConsole("Successfully cleaned leaderboard");
    else
        Logger::printWarningOnConsole("Cleaning leaderboard operation failure");
}


/**
 * Clears app's all data
 * @author Arthur
 * @date 22/12/16
 */
void DataBase::clearAppData()
{
    createConfigFile();
    fetchConfigurationFromFile();
    m_activatedItemsArray.clear();

    Logger::printInfoOnConsole("App data was successfully cleared");
}


/**
 * Looks for an item in the activated items array
 * @author Arthur
 * @date 31/10/17
 *
 * @param item the item to find
 * @return true if found
 */
bool DataBase::findActivatedItem(const string &item)
{
    return m_activatedItemsArray.empty()
           ? false
           : m_activatedItemsArray.find(item) != m_activatedItemsArray.end();
}


/**
 * Retrieves a localized string for a given label
 *
 * @param label the label to describe the string
 * @return the localized string
 *
 * @author Arthur
 * @date 04/01/17 - 24/01/18
 */
string DataBase::loadLocalizedString(const string &label) const
{
    string currentLocaleFile = getLanguageFile();
    return XMLPersistenceHelper::loadLabeledString(currentLocaleFile, label);
}


/**
 * Fills a string with the scores of a given difficulty,
 * extracted from a string array
 *
 * @param difficulty for the difficulty related scores
 * @return a string containing scores of a given difficulty
 *
 * @author Arthur
 * @date 23/10/16 - 24/01/18
 */
string DataBase::loadLeaderboardScores(Difficulty difficulty) const
{
    string result;
    std::set<int> scoresArray;

    if (difficulty == EASY && !isScoreEasyArrayEmpty())
    {
        result = loadLocalizedString("config_easy_mode") + " :\n";
        scoresArray = m_scoresEasyArray;
    }
    else if (difficulty == HARD && !isScoreHardArrayEmpty())
    {
        result = loadLocalizedString("config_hard_mode") + " :\n";
        scoresArray = m_scoresHardArray;
    }

    if (!scoresArray.empty())
    {
        int scoreRank = 1;
        for (auto it = scoresArray.rbegin(); it!=scoresArray.rend(); ++it)
        {
            result += "\n" + to_string(scoreRank) + (scoreRank != 10 ? ".   " : ". ") + to_string(*it);
            scoreRank++;
        }
    }

    return result;
}

