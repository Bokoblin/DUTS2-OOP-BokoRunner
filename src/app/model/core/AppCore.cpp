#include <app/persistence/PersistenceManager.h>

using std::string;
using std::to_string;
using Bokoblin::SimpleLogger::Logger;
namespace ViewResources = Bokoblin::BokoRunner::Resources::Model;

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
 * @date 26/11/17 - 13/10/18
 */
AppCore::~AppCore()
{
    cleanupShopItemsArray();
}


//------------------------------------------------
//          GETTERS
//------------------------------------------------

AppState AppCore::getAppState() const { return m_appState; }
int AppCore::getDifficulty() const { return m_currentDifficulty;}
int AppCore::getWallet() const { return m_wallet;}
bool AppCore::isMenuMusicEnabled() const { return m_isMenuMusicEnabled; }
bool AppCore::isGameMusicEnabled() const { return m_isGameMusicEnabled; }
std::vector<ShopItem*> AppCore::getShopItemsArray() const { return m_shopItemsArray; }
std::map<string, int> AppCore::getStatsMap() const { return m_statsMap; }
std::map<string, int> AppCore::getGameMap() const { return m_gameMap; }
bool AppCore::isScoreEasyArrayEmpty() const { return m_scoresEasyArray.empty(); }
bool AppCore::isScoreHardArrayEmpty() const { return m_scoresHardArray.empty(); }
string AppCore::getLanguage() const { return m_currentLanguage; }
string AppCore::getBallSkin() const { return m_currentBallSkin; }
string AppCore::getPersistenceContext() const { return PersistenceManager::getContextLocation(); }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void AppCore::setAppState(const AppState& state) { m_appState = state; }
void AppCore::setLanguage(const string& language) { m_currentLanguage = language; }
void AppCore::setBallSkin(const string& skin) { m_currentBallSkin = skin; }
void AppCore::setDifficulty(const Difficulty& difficulty) { m_currentDifficulty = difficulty; }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Saves the current game results to app data.
 *
 * @author Arthur
 * @date 02/05/16 - 13/01/19
 */
void AppCore::saveCurrentGame()
{
    //add current game values to total values
    m_statsMap["total_coins_collected"] += m_gameMap["coin_number"];
    m_statsMap["total_distance_travelled"] += m_gameMap["distance"];
    m_statsMap["total_enemies_destroyed"] += m_gameMap["enemies_destroyed"];
    m_wallet += m_gameMap["coin_number"];
    addNewScore(m_gameMap["score"]);

    //update per game stats if better
    m_statsMap["per_game_coins_collected"] =
            std::max(m_gameMap["coin_number"], m_statsMap["per_game_coins_collected"]);
    m_statsMap["per_game_distance_travelled"] =
            std::max(m_gameMap["distance"], m_statsMap["per_game_distance_travelled"]);
    m_statsMap["per_game_enemies_destroyed"] =
            std::max(m_gameMap["enemies_destroyed"], m_statsMap["per_game_enemies_destroyed"]);

    Logger::printInfo("Current game saved");
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

        Logger::printInfo("New score saved in EASY leaderboard");
    } else {
        m_scoresHardArray.insert(score);
        while (m_scoresHardArray.size() > MAX_SCORES) {
            m_scoresHardArray.erase(m_scoresHardArray.begin());
        }

        Logger::printInfo("New score saved in HARD leaderboard");
    }
}


/**
 * Resets current game to create a new one
 *
 * @author Arthur
 * @date 02/05/16 - 13/01/19
 */
void AppCore::launchNewGame()
{
    //for launching a new game
    m_statsMap["total_games_played"] += 1;
    m_gameMap["coin_number"] = 0;
    m_gameMap["distance"] = 0;
    m_gameMap["enemies_destroyed"] = 0;
    m_gameMap["score"] = 0;
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
        Logger::printInfo("Successfully cleaned leaderboard");
    } else {
        Logger::printWarning("Cleaning leaderboard operation failure");
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
    Logger::Logger::printInfo("App data was successfully cleared");
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
 * @date ?? - 13/01/19
 */
void AppCore::calculateFinalScore(float speed, int flattenedEnemiesBonus)
{
    float distanceSubScore = speed * m_gameMap.at("distance");
    int coinSubScore = COIN_MULTIPLIER * m_gameMap.at("coin_number");
    m_gameMap.at("score") = static_cast<int>(distanceSubScore + coinSubScore + flattenedEnemiesBonus);
}


/**
 * Fills a string with the scores of a given difficulty,
 * extracted from a string array
 *
 * @param difficulty for the difficulty related scores
 * @return a string containing scores of a given difficulty
 *
 * @author Arthur
 * @date 23/10/16 - 13/01/19
 */
string AppCore::stringifyLeaderboard(const Difficulty& difficulty) const
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
 * @date 04/02/18 - 13/01/19
 */
void AppCore::initWithDefaultValues()
{
    m_currentLanguage = "en";
    m_currentBallSkin = "default";
    m_currentDifficulty = HARD;
    m_isMenuMusicEnabled = false;
    m_isGameMusicEnabled = true;
    m_wallet = 0;

    for (auto elem : m_statsMap) {
        elem.second = 0;
    }

    for (auto elem : m_gameMap) {
        elem.second = 0;
    }

    m_scoresEasyArray.clear();
    m_scoresHardArray.clear();
    m_shopItemsArray.clear();
    m_activatedItemsArray.clear();
}

/**
 * Cleanup the shop items array
 *
 * @author Arthur
 * @date 02/05/2020
 */
void AppCore::cleanupShopItemsArray()
{
    for (ShopItem* shopItem: m_shopItemsArray) {
        delete shopItem;
    }
    m_shopItemsArray.clear();
}


/**
 * Decreases the wallet amount
 * @param amount the amount to remove
 *
 * @author Arthur
 * @date 02/05/16 - 13/01/19
 */
void AppCore::decreaseWallet(int amount)
{
    if (m_wallet - amount > 0) {
        m_wallet -= amount;
    } else {
        m_wallet = 0;
    }
}


/**
 * Increases the amount of collected coins
 * in the current game
 * @param amount the amount to add
 *
 * @author Arthur
 * @date 02/05/16 - 13/01/19
 */
void AppCore::increaseCurrentCoinsCollected(int amount) { m_gameMap.at("coin_number") += amount; }


/**
 * Increases the distance in the current game
 * @param amount the amount to add
 *
 * @author Arthur
 * @date 02/05/16 - 13/01/19
 */
void AppCore::increaseCurrentDistance(float amount) {
    Logger::printWarning(to_string(amount));
    m_gameMap.at("distance") += static_cast<int>(amount); }


/**
 * Increases the number of enemies killed
 *
 * @author Arthur
 * @date 02/05/16 - 13/01/19
 */
void AppCore::increaseCurrentFlattenedEnemies() {m_gameMap.at("enemies_destroyed")++; }


/**
 * Toggles the menu music
 *
 * @author Arthur
 * @date 02/05/16 - 04/02/2018
 */
void AppCore::toggleMenuMusic() { m_isMenuMusicEnabled = !m_isMenuMusicEnabled; }


/**
 * Toggles the game music
 *
 * @author Arthur
 * @date 02/05/16 - 04/02/2018
 */
void AppCore::toggleGameMusic() { m_isGameMusicEnabled = !m_isGameMusicEnabled; }
