/* Copyright 2016-2019 Jolivet Arthur & Laronze Florian

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef APP_CORE_H
#define APP_CORE_H

#include <set>
#include <map>
#include <vector>
#include "libs/Logger/Logger.h"
#include "app/localization/LocalizationManager.h"
#include "app/model/enums/AppState.h"
#include "app/model/enums/Difficulty.h"
#include "app/model/menu-components/ShopItem.h"
#include "app/persistence/FileBasedPersistence.h"
#include "ModelConstants.h"

/**
 * The AppCore class centralises app's state,
 * configuration, statistics, bonus, scores,
 * and current game's values. \n
 * It allows accessing, modifying app data and state
 * directly or for specific actions involving data changes
 *
 * to do specific actions to the app
 *
 * @author Arthur
 * @date 02/05/16 - 13/01/19
 */
class AppCore
{
public:
    //=== CTORs / DTORs
    AppCore();
    AppCore(const AppCore& d) = delete;
    virtual ~AppCore();

    //=== GETTERS
    AppState getAppState() const;
    int getWallet() const;
    int getDifficulty() const;
    bool isMenuMusicEnabled() const;
    bool isGameMusicEnabled() const;
    std::vector<ShopItem*> getShopItemsArray() const;
    std::map<std::string, int> getStatsMap() const;
    std::map<std::string, int> getGameMap() const;
    bool isScoreEasyArrayEmpty() const;
    bool isScoreHardArrayEmpty() const;
    std::string getLanguage() const;
    std::string getPlayerSkin() const;
    //FIXME [2.0.x] LINKED TO FILE BASED, WE SHALL ABSTRACT THAT ALSO
    virtual std::string getPersistenceContext() const;

    //=== SETTERS
    void setAppState(const AppState& state);
    void setDifficulty(const Difficulty& difficulty);
    void setLanguage(const std::string& language);
    void setPlayerSkin(const std::string& skin);

    //=== METHODS
    void addNewScore(int score);
    void saveCurrentGame();
    void launchNewGame();
    void clearLeaderboard();
    void clearAppData();
    bool findActivatedItem(const std::string& itemLabel);
    void addNewActivatedBonus(const std::string& itemLabel);
    void calculateFinalScore(float speed, int flattenedEnemiesBonus);
    std::string stringifyLeaderboard(const Difficulty& difficulty) const;
    void decreaseWallet(int amount);
    void increaseCurrentCoinsCollected(int amount);
    void increaseCurrentDistance(float amount);
    void increaseCurrentFlattenedEnemies();
    void toggleMenuMusic();
    void toggleGameMusic();

protected:
    //=== ATTRIBUTES

    //Global App
    AppState m_appState;
    int m_wallet;
    int m_currentDifficulty;
    bool m_isMenuMusicEnabled;
    bool m_isGameMusicEnabled;
    std::string m_currentLanguage;
    std::string m_currentPlayerSkin;
    const int COIN_MULTIPLIER = 20;
    const unsigned int MAX_SCORES = 10;

    //Containers
    std::set<int> m_scoresEasyArray;
    std::set<int> m_scoresHardArray;
    std::vector<ShopItem*> m_shopItemsArray;
    std::set<std::string> m_activatedItemsArray;
    std::map<std::string, int> m_statsMap;
    std::map<std::string, int> m_gameMap;

private:
    friend class FileBasedPersistence; //TODO [2.0.x] Be friend with an abstraction of persistence instead

    //=== METHODS
    void initWithDefaultValues();
    void cleanupShopItemsArray();
};

#endif
