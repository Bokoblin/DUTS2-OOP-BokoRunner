#include "DataBase.h"

using std::string;
using std::to_string;
using Bokoblin::SimpleLogger::Logger;

//------------------------------------------------
//          CONSTRUCTOR / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs the app's database by initializing
 * all its data
 *
 * @author Arthur
 * @date 02/05/16 - 04/02/18
 */
DataBase::DataBase() : m_appState{SPLASH}
{
    initWithDefaultValues();
}


/**
 * Destructor
 * @author Arthur
 * @date 26/11/17
 */
DataBase::~DataBase() = default;


//------------------------------------------------
//          GETTERS
//------------------------------------------------

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


//------------------------------------------------
//          SETTERS
//------------------------------------------------

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


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Saves the current game results to app data.
 *
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
 *
 * @param score to add to the score array
 *
 * @author Arthur
 * @date 23/10/16 - 23/01/17
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
 * Resets current game to create a new one
 *
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
 * Clears the leaderboard data
 *
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
 *
 * @author Arthur
 * @date 22/12/16 - 04/02/18
 */
void DataBase::clearAppData()
{
    initWithDefaultValues();
    Logger::printInfoOnConsole("App data was successfully cleared");
}


/**
 * Looks for an item in the activated items array
 *
 * @param itemLabel the item to look for
 * @return a boolean for searching result
 *
 * @author Arthur
 * @date 31/10/17
 */
bool DataBase::findActivatedItem(const string &itemLabel)
{
    return m_activatedItemsArray.empty()
           ? false
           : m_activatedItemsArray.find(itemLabel) != m_activatedItemsArray.end();
}


/**
 * Add a newly activated bonus to the item array
 *
 * @param itemLabel the item label
 *
 * @author Arthur
 * @date 04/02/18
 */
void DataBase::addNewActivatedBonus(const string &itemLabel)
{
    m_activatedItemsArray.insert(itemLabel);
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
string DataBase::stringifyLeaderboard(Difficulty difficulty) const
{
    string result;
    std::set<int> scoresArray;

    if (difficulty == EASY && !isScoreEasyArrayEmpty())
    {
        result = PersistenceManager::fetchLocalizedString("config_easy_mode") + " :\n";
        scoresArray = m_scoresEasyArray;
    }
    else if (difficulty == HARD && !isScoreHardArrayEmpty())
    {
        result = PersistenceManager::fetchLocalizedString("config_hard_mode") + " :\n";
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


//------------------------------------------------
//          PRIVATE METHODS
//------------------------------------------------

/**
 * Inits the application with default value
 * in order to not rely on persistence context
 * in case it hasn't been initialized
 *
 * @author Arthur
 * @date 04/02/18
 */
void DataBase::initWithDefaultValues()
{
    m_currentLanguage = "en";
    m_currentBallSkin = "default";
    m_currentDifficulty = HARD;
    m_isMenuMusicEnabled = false;
    m_isGameMusicEnabled = true;
    m_wallet = 0;

    m_totalCoinsCollected = 0;
    m_totalDistance = 0;
    m_totalFlattenedEnemies = 0;
    m_totalGamesPlayed = 0;
    m_perGameCoinsCollected = 0;
    m_perGameDistance = 0;
    m_perGameFlattenedEnemies = 0;

    m_scoreBonusFlattenedEnemies = 0;

    m_scoresEasyArray.clear();
    m_scoresHardArray.clear();
    m_activatedItemsArray.clear();

    m_currentCoinsNumber = 0;
    m_currentDistance = 0;
    m_currentFlattenedEnemies = 0;
    m_currentScore = 0;
}
