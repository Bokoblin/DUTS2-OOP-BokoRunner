#include "AppCore.h"

using std::string;
using std::to_string;
using Bokoblin::SimpleLogger::Logger;

//------------------------------------------------
//          CONSTRUCTOR / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs the app core
 * by initializing all its data
 *
 * @author Arthur
 * @date 02/05/16 - 04/02/18
 */
AppCore::AppCore() : m_appState{SPLASH}
{
    initWithDefaultValues();
}


/**
 * Destructor
 * @author Arthur
 * @date 26/11/17
 */
AppCore::~AppCore() = default;


//------------------------------------------------
//          GETTERS
//------------------------------------------------

AppState AppCore::getAppState() const { return m_appState; }
int AppCore::getTotalCoinsNumber() const { return m_totalCoinsCollected; }
int AppCore::getTotalDistance() const { return m_totalDistance; }
int AppCore::getTotalFlattenedEnemies() const { return m_totalFlattenedEnemies; }
int AppCore::getTotalGamesPlayed() const { return m_totalGamesPlayed; }
int AppCore::getPerGameCoinsNumber() const { return m_perGameCoinsCollected; }
int AppCore::getPerGameDistance() const { return m_perGameDistance; }
int AppCore::getPerGameFlattenedEnemies() const { return m_perGameFlattenedEnemies; }
int AppCore::getCurrentCoinsNumber() const { return m_currentCoinsNumber; } //for display purpose
int AppCore::getCurrentDistance() const { return static_cast<int>(m_currentDistance); }
int AppCore::getCurrentFlattenedEnemies() const { return m_currentFlattenedEnemies; } //for display purpose
int AppCore::getCurrentScore() const { return m_currentScore; } //for display purpose
int AppCore::getDifficulty() const { return m_currentDifficulty;}
int AppCore::getWallet() const { return m_wallet;}
bool AppCore::isMenuMusicEnabled() const { return m_isMenuMusicEnabled; }
bool AppCore::isGameMusicEnabled() const { return m_isGameMusicEnabled; }
bool AppCore::isScoreEasyArrayEmpty() const { return m_scoresEasyArray.empty(); }
bool AppCore::isScoreHardArrayEmpty() const { return m_scoresHardArray.empty(); }
string AppCore::getLanguage() const { return m_currentLanguage; }
string AppCore::getBallSkin() const { return m_currentBallSkin; }
string AppCore::getConfigFile() const { return CONFIG_FILE; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void AppCore::setAppState(AppState state) { m_appState = state; }
void AppCore::setLanguage(const string& language) { m_currentLanguage = language; }
void AppCore::setBallSkin(const string& skin) { m_currentBallSkin = skin; }
void AppCore::setDifficulty(int difficulty) { m_currentDifficulty = difficulty; }
void AppCore::decreaseWallet(int amount) { m_wallet -= amount; }
void AppCore::increaseCurrentCoinsCollected(int amount) { m_currentCoinsNumber += amount; }
void AppCore::increaseCurrentDistance(float amount) { m_currentDistance += amount; }
void AppCore::increaseCurrentFlattenedEnemies() { m_currentFlattenedEnemies += 1; }
void AppCore::toggleMenuMusic() { m_isMenuMusicEnabled = !m_isMenuMusicEnabled; }
void AppCore::toggleGameMusic() { m_isGameMusicEnabled = !m_isGameMusicEnabled; }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Saves the current game results to app data.
 *
 * @author Arthur
 * @date 02/05/16 - 14/01/17
 */
void AppCore::saveCurrentGame()
{
    //add current game values to total values
    m_totalCoinsCollected += m_currentCoinsNumber;
    m_wallet += m_currentCoinsNumber;
    m_totalDistance += static_cast<int>(m_currentDistance);
    m_totalFlattenedEnemies += m_currentFlattenedEnemies;
    addNewScore(m_currentScore);

    //update per game stats if better
    if (m_currentCoinsNumber > m_perGameCoinsCollected) {
        m_perGameCoinsCollected = m_currentCoinsNumber;
    }
    if (m_currentDistance > m_perGameDistance) {
        m_perGameDistance = static_cast<int>(m_currentDistance);
    }
    if (m_currentFlattenedEnemies > m_perGameFlattenedEnemies) {
        m_perGameFlattenedEnemies = m_currentFlattenedEnemies;
    }

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
void AppCore::addNewScore(int score)
{
    if (m_currentDifficulty == EASY) {
        m_scoresEasyArray.insert(score);
        while (m_scoresEasyArray.size() > MAX_SCORES) {
            m_scoresEasyArray.erase(m_scoresEasyArray.begin());
        }

        Logger::printInfoOnConsole("New score saved in EASY leaderboard");
    } else {
        m_scoresHardArray.insert(score);
        while (m_scoresHardArray.size() > MAX_SCORES) {
            m_scoresHardArray.erase(m_scoresHardArray.begin());
        }

        Logger::printInfoOnConsole("New score saved in HARD leaderboard");
    }
}


/**
 * Resets current game to create a new one
 *
 * @author Arthur
 * @date 02/05/16
 */
void AppCore::launchNewGame()
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
void AppCore::clearLeaderboard()
{
    m_scoresEasyArray.clear();
    m_scoresHardArray.clear();

    if (m_scoresEasyArray.empty() && m_scoresHardArray.empty()) {
        Logger::printInfoOnConsole("Successfully cleaned leaderboard");
    } else {
        Logger::printWarningOnConsole("Cleaning leaderboard operation failure");
    }
}


/**
 * Clears app's all data
 *
 * @author Arthur
 * @date 22/12/16 - 04/02/18
 */
void AppCore::clearAppData()
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
bool AppCore::findActivatedItem(const string& itemLabel)
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
void AppCore::addNewActivatedBonus(const string& itemLabel)
{
    m_activatedItemsArray.insert(itemLabel);
}

/**
 * Calculates the final score at game over
 *
 * @param speed the last game speed before game over
 * @param flattenedEnemiesBonus the bonus for all enemies flattened in the last game
 *
 * @author Arthur
 * @date ?? - 04/02/18
 */
void AppCore::calculateFinalScore(float speed, int flattenedEnemiesBonus)
{
    m_currentScore = static_cast<int>(
            (speed * m_currentDistance) + (COIN_MULTIPLIER * m_currentCoinsNumber) + flattenedEnemiesBonus);
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
string AppCore::stringifyLeaderboard(Difficulty difficulty) const
{
    string result;
    std::set<int> scoresArray;

    if (difficulty == EASY && !isScoreEasyArrayEmpty()) {
        result = LocalizationManager::fetchLocalizedString("config_easy_mode") + " :\n";
        scoresArray = m_scoresEasyArray;
    } else if (difficulty == HARD && !isScoreHardArrayEmpty()) {
        result = LocalizationManager::fetchLocalizedString("config_hard_mode") + " :\n";
        scoresArray = m_scoresHardArray;
    }

    if (!scoresArray.empty()) {
        int scoreRank = 1;
        for (auto it = scoresArray.rbegin(); it != scoresArray.rend(); ++it) {
            result += "\n" + to_string(scoreRank) + (scoreRank < 10 ? ".   " : ". ") + to_string(*it);
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
void AppCore::initWithDefaultValues()
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

    m_scoresEasyArray.clear();
    m_scoresHardArray.clear();
    m_activatedItemsArray.clear();

    m_currentCoinsNumber = 0;
    m_currentDistance = 0;
    m_currentFlattenedEnemies = 0;
    m_currentScore = 0;
}
