#include "DataBase.h"

using namespace std;


/**
 * Constructs the app's database by initializing
 * all the data from config (backup) file
 * @author Arthur
 * @date 02/05/16 - 29/01/17
 */
DataBase::DataBase() :
    m_currentCoinsNumber{0}, m_currentDistance{0}, m_currentFlattenedEnemies{0},
    m_currentScore{0}, m_isMenuMusicEnabled{false}, m_isGameMusicEnabled{false},
    m_appState{INTRO}, m_scoreBonusFlattenedEnemies{0}
{
    if (!checkConfigFileIntegrity())
        createConfigFile();
    fetchConfigurationFromFile();
}


//=== Getters

AppState DataBase::getAppState() const {return m_appState;}
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
int DataBase::getDifficulty() const {return m_currentDifficulty;}
int DataBase::getWallet() const {return m_wallet;}
bool DataBase::isMenuMusicEnabled() const {return m_isMenuMusicEnabled;}
bool DataBase::isGameMusicEnabled() const {return m_isGameMusicEnabled;}
string DataBase::getLanguage() const { return m_currentLanguage;}
string DataBase::getBallSkin() const { return m_currentBallSkin; }
const set<string>& DataBase::getActivatedItemsArray() const { return m_activatedItemsArray; }
string DataBase::getLanguageFile() const
{
    if (m_currentLanguage == "en")
        return ENGLISH_STRINGS;
    else if (m_currentLanguage == "fr")
        return FRENCH_STRINGS;
    else if (m_currentLanguage == "es")
        return SPANISH_STRINGS;
    else
        return "null"; //TODO: Throw exception
}


//=== Setters

void DataBase::setAppState(AppState state) { m_appState = state;}
void DataBase::decreaseWallet(int amount) { m_wallet -= amount; }
void DataBase::increaseCurrentCoinsCollected(int amount) { m_currentCoinsNumber += amount; }
void DataBase::increaseCurrentDistance(float amount) { m_currentDistance += amount; }
void DataBase::increaseCurrentFlattenedEnemies(int amount) {
    m_scoreBonusFlattenedEnemies += amount;
    m_currentFlattenedEnemies += 1;
}
void DataBase::setLanguage(string lang) { m_currentLanguage = lang;}
void DataBase::setBallSkin(string skin) { m_currentBallSkin = skin; }
void DataBase::setDifficulty(int d) { m_currentDifficulty = d;}
void DataBase::setMenuMusic(bool on) { m_isMenuMusicEnabled = on; }
void DataBase::setGameMusic(bool on) { m_isGameMusicEnabled = on;}
void DataBase::setCurrentScore(float speed)
{
    m_currentScore = (int)(speed * m_currentDistance
                     + COIN_MULTIPLIER*m_currentCoinsNumber + m_scoreBonusFlattenedEnemies);
}


/**
 * (Re)creates config file
 * @author Arthur
 * @date 02/05/16 - 24/10/16
 */
void DataBase::createConfigFile()
{
    fstream f;
    f.open(CONFIG_FILE.c_str(), ios::out);
    f << DEFAULT_CONFIG_CONTENT;
    f.close();
}


/**
 * Checks if config file has been corrupted
 * by verifying file number of lines, number of each item
 * @author Arthur
 * @date 02/05/16 - 25/01/17
 *
 * @return a boolean indicating if file is corrupted
 */
bool DataBase::checkConfigFileIntegrity() const
{
    fstream f;
    string line;

    f.open(CONFIG_FILE.c_str(), ios::in);

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
    }
    while (!f.eof());

    return !(!isPresentConfig || !isPresentStats || !isPresentShop || !isPresentScoreEasy || !isPresentScoreHard
             || (nbLines != 52 && nbLines != 53)
             || nbConfigChildren!=6 || nbStatsChildren!=7 || nbShopChildren!=6 || nbScoreChildren!=20);
}


/**
 * Fetches Configuration data from file
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
 * @author Arthur
 * @date 24/10/16 - 25/01/17
 */
void DataBase::fetchConfig()
{
    pugi::xml_document doc;
    doc.load_file(CONFIG_FILE.c_str());

    pugi::xml_node runner = doc.child("runner");
    pugi::xml_node config = runner.child("config");
    pugi::xml_node stats = runner.child("stats");

    for (pugi::xml_node configItem: config.children("configItem"))
    {
        if (string(configItem.attribute("name").value()) == "language")
            m_currentLanguage = configItem.attribute("value").value();
        if (string(configItem.attribute("name").value()) == "difficulty")
            m_currentDifficulty = atoi(configItem.attribute("value").value());
        else if (string(configItem.attribute("name").value()) == "ball_skin")
            m_currentBallSkin = configItem.attribute("value").value();
        else if (string(configItem.attribute("name").value()) == "wallet")
            m_wallet = atoi(configItem.attribute("value").value());
        else if (string(configItem.attribute("name").value()) == "menu_music")
        {
            string result = configItem.attribute("value").value();
            if (result == "true") m_isMenuMusicEnabled=true;
        }
        else if (string(configItem.attribute("name").value()) == "game_music")
        {
            string result = configItem.attribute("value").value();
            if (result == "true") m_isGameMusicEnabled=true;
        }
    }

    for (pugi::xml_node statItem: stats.children("statItem"))
    {
        if (string(statItem.attribute("name").value()) == "total_coins_collected")
            m_totalCoinsCollected = atoi(statItem.attribute("value").value());
        else if (string(statItem.attribute("name").value()) == "total_distance_travelled")
            m_totalDistance = atoi(statItem.attribute("value").value());
        else if (string(statItem.attribute("name").value()) == "total_enemies_destroyed")
            m_totalFlattenedEnemies = atoi(statItem.attribute("value").value());
        else if (string(statItem.attribute("name").value()) == "per_game_coins_collected")
            m_perGameCoinsCollected = atoi(statItem.attribute("value").value());
        else if (string(statItem.attribute("name").value()) == "per_game_distance_travelled")
            m_perGameDistance = atoi(statItem.attribute("value").value());
        else if (string(statItem.attribute("name").value()) == "per_game_enemies_destroyed")
            m_perGameFlattenedEnemies = atoi(statItem.attribute("value").value());
        else if (string(statItem.attribute("name").value()) == "total_games_played")
            m_totalGamesPlayed = atoi(statItem.attribute("value").value());
    }
}


/**
 * Updates each score array
 * with values from config file
 * @author Arthur
 * @date 23/10/16 - 23/01/17
 */
void DataBase::fetchScore()
{
    pugi::xml_document doc;
    doc.load_file(CONFIG_FILE.c_str());

    pugi::xml_node runner = doc.child("runner");
    pugi::xml_node scoresEasy = runner.child("scoresEasy");
    pugi::xml_node scoresHard = runner.child("scoresHard");

    m_scoresEasyArray.clear();
    m_scoresHardArray.clear();
    for (pugi::xml_node scoreItem: scoresEasy.children("scoreItem"))
    {
        if (string(scoreItem.attribute("value").value()) != "0")
            m_scoresEasyArray.insert(atoi(scoreItem.attribute("value").value()));
    }
    for (pugi::xml_node scoreItem: scoresHard.children("scoreItem"))
    {
        if (string(scoreItem.attribute("value").value()) != "0")
            m_scoresHardArray.insert(atoi(scoreItem.attribute("value").value()));
    }
}


/**
 * Updates activated items array
 * @author Arthur
 * @date 14/05/16 - 24/10/16
 */
void DataBase::fetchActivatedShopItems()
{
    pugi::xml_document doc;
    doc.load_file(CONFIG_FILE.c_str());

    pugi::xml_node runner = doc.child("runner");
    pugi::xml_node shop = runner.child("shop");

    for (pugi::xml_node shopItem: shop.children("shopItem"))
    {
        if (string(shopItem.attribute("bought").value()) == "true")
            m_activatedItemsArray.insert(shopItem.attribute("id").value());
    }
}


/**
 * Pushes Configuration data to file
 * @author Arthur
 * @date 02/05/16 - 24/01/17
 */
void DataBase::pushConfigurationToFile() const
{
    pugi::xml_document doc;
    doc.load_file(CONFIG_FILE.c_str());

    pugi::xml_node runner = doc.child("runner");
    pugi::xml_node config = runner.child("config");
    pugi::xml_node stats = runner.child("stats");
    pugi::xml_node scoresEasy = runner.child("scoresEasy");
    pugi::xml_node scoresHard = runner.child("scoresHard");

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
    set<int>::iterator it = m_scoresEasyArray.begin();
    for (pugi::xml_node scoreItem: scoresEasy.children("scoreItem"))
    {
        if (it!=m_scoresEasyArray.end())
        {
            pugi::xml_attribute nodeValue = scoreItem.attribute("value");
            nodeValue.set_value((to_string(*it)).c_str());
            ++it;
        }
        else
        {
            pugi::xml_attribute nodeValue = scoreItem.attribute("value");
            nodeValue.set_value("0");
        }
    }

    it = m_scoresHardArray.begin();
    for (pugi::xml_node scoreItem: scoresHard.children("scoreItem"))
    {
        if (it!=m_scoresHardArray.end())
        {
            pugi::xml_attribute nodeValue = scoreItem.attribute("value");
            nodeValue.set_value((to_string(*it)).c_str());
            ++it;
        }
        else
        {
            pugi::xml_attribute nodeValue = scoreItem.attribute("value");
            nodeValue.set_value("0");
        }
    }

    doc.save_file(CONFIG_FILE.c_str());
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
    }
    else
    {
        m_scoresHardArray.insert(score);
        while (m_scoresHardArray.size() > MAX_SCORES)
            m_scoresHardArray.erase(m_scoresHardArray.begin());
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
}


/**
 * Gets language-adapted string
 * from language string file
 * to affect to a Text object
 * @author Arthur
 * @date 04/01/17
 *
 * @param description to fetch corresponding content
 * @return text string
 */
string DataBase::getTextValueFromStringsFile(const string &description) const
{
    pugi::xml_document doc;
    doc.load_file(getLanguageFile().c_str());

    pugi::xml_node resources = doc.child("resources");

    for (pugi::xml_node item: resources.children("string"))
    {
        if (string(item.attribute("name").value()) == description)
        {
            return item.attribute("value").value();
        }
    }
    return "unknown";
}


/**
 * Updates string content from array
 * @author Arthur
 * @date 23/10/16 - 23/01/17
 *
 * @param difficulty for the difficulty related scores
 * @return a string containing scores of a given difficulty
 */
string DataBase::loadLeaderboardStringFromArray(Difficulty difficulty) const
{
    int i = 1;
    string result = "";

    if (difficulty == EASY && !m_scoresEasyArray.empty())
    {
        result = getTextValueFromStringsFile("config_easy_mode") + " :\n";
        //add each case content in string
        for (set<int>::reverse_iterator it = m_scoresEasyArray.rbegin(); it!=m_scoresEasyArray.rend(); ++it)
        {
            if (i != 10)
                result += "\n" + to_string(i) + ".   " + to_string(*it);
            else
                result += "\n" + to_string(i) + ". " + to_string(*it);
            i++;
        }
    }
    else if (difficulty == HARD &&!m_scoresHardArray.empty())
    {
        result = getTextValueFromStringsFile("config_hard_mode") + " :\n";
        for (set<int>::reverse_iterator it = m_scoresHardArray.rbegin(); it!=m_scoresHardArray.rend(); ++it)
        {
            if (i != 10)
                result += "\n" + to_string(i) + ".   " + to_string(*it);
            else
                result += "\n" + to_string(i) + ". " + to_string(*it);
            i++;
        }
    }
    return result;
}

