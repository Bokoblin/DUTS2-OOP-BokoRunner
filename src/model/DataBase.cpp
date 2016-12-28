#include "DataBase.h"

using namespace std;


/**
 * Default Constructor
 * @author Arthur
 * @date 2/05
 */
DataBase::DataBase() :
    m_currentCoinsNumber{0}, m_currentDistance{0},
    m_currentFlattenedEnemies{0}, m_currentScore{0}
{
    if (!checkFileIntegrity())
        createFile();
    fetchConfigurationFromFile();
}


//=== Getters

int DataBase::getTotalCoinsNumber() const { return m_totalCoinsCollected; }
int DataBase::getTotalDistance() const { return m_totalDistance; }
int DataBase::getTotalFlattenedEnemies() const { return m_totalFlattenedEnemies; }
int DataBase::getTotalGamesPlayed() const { return m_totalGamesPlayed; }
int DataBase::getCurrentCoinsNumber() const { return m_currentCoinsNumber; }
int DataBase::getCurrentDistance() const { return (int)m_currentDistance; }
int DataBase::getCurrentFlattenedEnemies() const { return m_currentFlattenedEnemies; }
int DataBase::getCurrentScore() const { return m_currentScore; }
string DataBase::getLanguage() const { return m_currentLanguage;}
int DataBase::getDifficulty() const {return m_currentDifficulty;}
string DataBase::getBallSkin() const { return m_currentBallSkin; }
const set<string>& DataBase::getActivatedItemsArray() const { return m_activatedItemsArray; }


//=== Setters

void DataBase::setTotalCoinsCollected(int n) { m_totalCoinsCollected += n; }
void DataBase::setCurrentCoinsCollected(int n) { m_currentCoinsNumber += n; }
void DataBase::increaseCurrentDistance(float n) { m_currentDistance += n; }
void DataBase::setCurrentFlattenedEnemies(int n) { m_currentFlattenedEnemies += n; }
void DataBase::setLanguage(string lang) { m_currentLanguage = lang;}
void DataBase::setBallSkin(string skin) { m_currentBallSkin = skin; }
void DataBase::setDifficulty(int d) { m_currentDifficulty = d;}
void DataBase::setCurrentScore(float speed)
{
    m_currentScore = (int)(speed * m_currentDistance
                            + COIN_MULTIPLIER*m_currentCoinsNumber + m_currentFlattenedEnemies );
}


/**
 * (Re)create files
 * @author Arthur
 * @date 2/05 - 24/10
 */
void DataBase::createFile()
{
    fstream f;
    f.open( CONFIG_FILE.c_str(), ios::out);
    f << DEFAULT_CONFIG_CONTENT;
    f.close();
}


/**
 * Check if file data is OK
 * @author Arthur
 * @date 2/05 - 20/12
 */
bool DataBase::checkFileIntegrity()
{
    fstream f;
    string line;

    f.open( CONFIG_FILE.c_str(), ios::in);

    //=== Opening test
    if ( f.fail() )
        return false;

    //=== Count lines / elements test
    bool isPresentConfig = false; //should be true
    bool isPresentShop = false; //should be true
    bool isPresentScore = false; //should be true
    int nbLines = 0; //should be 32 or 33
    int nbConfigChildren = 0; //should be 7
    int nbShopChildren = 0; //should be 6
    int nbScoreChildren = 0; //should be 10
    do {
        getline(f, line, '\n');
        nbLines++;

        unsigned long long int found = line.find("<config>");
        if ( found != string::npos)
            isPresentConfig = true;

        found = line.find("<shop>");
        if ( found != string::npos)
            isPresentShop = true;

        found = line.find("<scores>");
        if ( found != string::npos)
            isPresentScore = true;

        found = line.find("<configItem");
        if ( found != string::npos)
            nbConfigChildren++;

        found = line.find("<shopItem");
        if ( found != string::npos)
            nbShopChildren++;

        found = line.find("<scoreItem");
        if ( found != string::npos)
            nbScoreChildren++;
    }
    while ( !f.eof() );

    return !(!isPresentConfig || !isPresentShop || !isPresentScore || (nbLines != 32 && nbLines != 33)
             || nbConfigChildren!=7 || nbShopChildren!=6 || nbScoreChildren!=10);
}


/**
 * Fetch Configuration data from file
 * @author Arthur
 * @date 2/05 - 24/10
 */
void DataBase::fetchConfigurationFromFile()
{
    updateConfigValues();
    updateScoreArray();
    updateActivatedItemsArray();
}


/**
 * Update variable value from file
 * @author Arthur
 * @date 24/10
 */
void DataBase::updateConfigValues()
{
    pugi::xml_document doc;
    doc.load_file(CONFIG_FILE.c_str());

    pugi::xml_node runner = doc.child("runner");
    pugi::xml_node config = runner.child("config");

    for (pugi::xml_node configItem: config.children("configItem"))
    {
        if (string(configItem.attribute("name").value()) == "language")
            m_currentLanguage = configItem.attribute("value").value();
        if (string(configItem.attribute("name").value()) == "difficulty")
            m_currentDifficulty = atoi(configItem.attribute("value").value());
        else if (string(configItem.attribute("name").value()) == "ball_skin")
            m_currentBallSkin = configItem.attribute("value").value();
        else if (string(configItem.attribute("name").value()) == "total_coins_collected")
            m_totalCoinsCollected = atoi(configItem.attribute("value").value());
        else if (string(configItem.attribute("name").value()) == "total_distance_travelled")
            m_totalDistance = atoi(configItem.attribute("value").value());
        else if (string(configItem.attribute("name").value()) == "total_enemies_destroyed")
            m_totalFlattenedEnemies = atoi(configItem.attribute("value").value());
        else if (string(configItem.attribute("name").value()) == "total_games_played")
            m_totalGamesPlayed = atoi(configItem.attribute("value").value());
    }
}


/**
 * Update score array
 * @author Arthur
 * @date 23/10 - 24/10
 */
void DataBase::updateScoreArray()
{
    pugi::xml_document doc;
    doc.load_file(CONFIG_FILE.c_str());

    pugi::xml_node runner = doc.child("runner");
    pugi::xml_node scores = runner.child("scores");

    m_scoresArray.clear();
    for (pugi::xml_node scoreItem: scores.children("scoreItem"))
    {
        if (string(scoreItem.attribute("value").value()) != "0")
            m_scoresArray.insert(atoi(scoreItem.attribute("value").value()));
    }
}


/**
 * Update array of activated items
 * @author Arthur
 * @date 14/05 - 24/10
 */
void DataBase::updateActivatedItemsArray()
{
    pugi::xml_document doc;
    doc.load_file(CONFIG_FILE.c_str());

    pugi::xml_node runner = doc.child("runner");
    pugi::xml_node shop = runner.child("shop");

    for (pugi::xml_node shopItem: shop.children("shopItem"))
    {
        if ( string(shopItem.attribute("boughtState").value()) == "true")
            m_activatedItemsArray.insert( shopItem.attribute("id").value() );
    }
}


/**
 * Push Configuration data to file
 * @author Arthur
 * @date 2/05 - 24/10
 */
void DataBase::pushConfigurationToFile()
{
    pugi::xml_document doc;
    doc.load_file(CONFIG_FILE.c_str());

    pugi::xml_node runner = doc.child("runner");
    pugi::xml_node config = runner.child("config");
    pugi::xml_node scores = runner.child("scores");

    //Save config
    for (pugi::xml_node configItem: config.children("configItem"))
    {
        if ( string(configItem.attribute("name").value()) == "language" )
        {
            pugi::xml_attribute nodeValue = configItem.attribute("value");
            nodeValue.set_value(m_currentLanguage.c_str());
        }
        if ( string(configItem.attribute("name").value()) == "difficulty" )
        {
            pugi::xml_attribute nodeValue = configItem.attribute("value");
            nodeValue.set_value((to_string(m_currentDifficulty)).c_str());
        }
        else if ( string(configItem.attribute("name").value()) == "ball_skin" )
        {
            pugi::xml_attribute nodeValue = configItem.attribute("value");
            nodeValue.set_value(m_currentBallSkin.c_str());
        }
        else if ( string(configItem.attribute("name").value()) == "total_coins_collected" )
        {
            pugi::xml_attribute nodeValue = configItem.attribute("value");
            nodeValue.set_value((to_string(m_totalCoinsCollected)).c_str());
        }
        else if ( string(configItem.attribute("name").value()) == "total_distance_travelled" )
        {
            pugi::xml_attribute nodeValue = configItem.attribute("value");
            nodeValue.set_value((to_string(m_totalDistance)).c_str());
        }
        else if ( string(configItem.attribute("name").value()) == "total_enemies_destroyed" )
        {
            pugi::xml_attribute nodeValue = configItem.attribute("value");
            nodeValue.set_value((to_string(m_totalFlattenedEnemies)).c_str());
        }
        else if ( string(configItem.attribute("name").value()) == "total_games_played" )
        {
            pugi::xml_attribute nodeValue = configItem.attribute("value");
            nodeValue.set_value((to_string(m_totalGamesPlayed)).c_str());
        }
    }

    //Save score
    set<int>::iterator it = m_scoresArray.begin();
    for (pugi::xml_node scoreItem: scores.children("scoreItem"))
    {
        if ( it!=m_scoresArray.end())
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
 * Save Current Game
 * @author Arthur
 * @date 2/05 - 26/12
 */
void DataBase::saveCurrentGame()
{
    //add current game values to total values
    m_totalCoinsCollected += m_currentCoinsNumber;
    m_totalDistance += (int)m_currentDistance;
    m_totalFlattenedEnemies += m_currentFlattenedEnemies;
    addEntryToScoreArray(m_currentScore);
}

/**
 * Add a new score to the score array
 * @author Arthur
 * @date 23/10
 */
void DataBase::addEntryToScoreArray(int new_score)
{
    m_scoresArray.insert(new_score);
    while (m_scoresArray.size() > MAX_SCORES)
        m_scoresArray.erase(m_scoresArray.begin());
}

/**
 * Update string content from array
 * @author Arthur
 * @date 23/10
 */
void DataBase::loadStringFromArray(std::string &scores_text)
{
    if (!m_scoresArray.empty())
    {
        //add each case content in string
        int i = 1;
        for (set<int>::reverse_iterator it = m_scoresArray.rbegin(); it!=m_scoresArray.rend(); ++it)
        {
            if ( i != 10)
                scores_text += "\n" + to_string(i) + ".   " + to_string(*it);
            else
                scores_text += "\n" + to_string(i) + ". " + to_string(*it);
            i++;
        }
    }
}

/**
 * Reset Current Game
 * @author Arthur
 * @date 2/05
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
 * Reset Score
 * @author Arthur
 * @date 24/10
 */
void DataBase::resetScore()
{
    m_scoresArray.clear();
}

/**
 * Reset Whole app
 * @author Arthur
 * @date 22/12
 */
void DataBase::resetWholeApp()
{
    createFile();
    fetchConfigurationFromFile();
    m_activatedItemsArray.clear();
}
