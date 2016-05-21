/* Copyright 2016 Jolivet Arthur & Laronze Florian

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

#ifndef _DATABASE_H
#define _DATABASE_H

#include "ShopItem.h"
#include "Leaderboard.h"
#include "../../Libs/pugixml-1.7/src/pugixml.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <set>

/********************************************
    Constant Variables
********************************************/
//GAME
const std::string CONFIG_FILE = "Resources/config.xml";
const std::string HIDDEN_CONFIG_FILE = "Resources/.fragment_cache";

const std::string DEFAULT_CONFIG_CONTENT = " \
<?xml version=\"1.0\" encoding=\"utf-8\"?>\n \
<runner>\n \
    <config>\n \
        <string name=\"language\">en</string>\n \
        <string name=\"ball_skin\">default</string>\n \
        <int name=\"total_coins_collected\">0</int>\n \
        <int name=\"total_distance_travelled\">0</int>\n \
        <int name=\"total_enemies_destroyed\">0</int>\n \
        <int name=\"total_games_played\">0</int>\n \
    </config>\n \
    <shop>\n \
        <item id=\"doubler\" name=\"Coin Doubler\" description=\"Double coins collected number\" price=\"500\" boughtState=\"false\"/>\n \
        <item id=\"shieldplus\" name=\"Increase Shield bonus\" description=\"Protect two times\" price=\"50\" boughtState=\"false\"/>\n \
        <item id=\"megaplus\" name=\"Increase Mega bonus\" description=\"Increase bonus duration by 5s\" price=\"100\" boughtState=\"false\"/>\n \
        <item id=\"flyplus\" name=\"Increase Fly bonus\" description=\"Increase bonus duration by 5s\" price=\"70\" boughtState=\"false\"/>\n \
        <item id=\"morphing\" name=\"Morph ball skin\" description=\"Unlock ball's morph skin\" price=\"300\" boughtState=\"false\"/>\n \
        <item id=\"capsule\" name=\"Capsule ball skin\" description=\"Unlock ball's capsule skin\" price=\"350\" boughtState=\"false\"/>\n \
    </shop>\n \
</runner>\n";


/********************************************
    DataBase Class
*********************************************
    @author Arthur  @date 2/05 - 21/05
*********************************************/
class DataBase
{
public:
    //=== CTORs / DTORs
    DataBase();
    DataBase(const DataBase& d)=delete;
    ~DataBase();

    //=== GETTERS
    int getTotalCoinsNumber() const;
    int getTotalDistance() const;
    int getTotalFlattenedEnemies() const;
    int getTotalGamesPlayed() const;
    int getCurrentCoinsNumber() const;
    int getCurrentDistance() const;
    int getCurrentFlattenedEnemies() const;
    int getCurrentScore() const;
    std::string getLanguage() const;
    std::string getBallSkin() const;
    const std::set<std::string>& getActivatedItemsArray() const;

    //=== SETTERS
    void setTotalCoinsCollected(int number);
    void setCurrentCoinsCollected(int number);
    void setCurrentDistance(int number);
    void setCurrentFlattenedEnemies(int number);
    void setCurrentScore(float speed);
    void setLanguage(std::string lang);
    void setBallSkin(std::string skin);

    //=== METHODS
    void createFile();
    bool checkFileIntegrity();
    void fetchConfigurationFromFile();
    void fetchBuyableItemsFromFile(std::vector<ShopItem*> &setArray);
    template <typename T>
    void updateValue(T &variable, std::string name);
    void updateActivatedItemsArray();
    void pushConfigurationToFile();
    void saveCurrentGame();
    void resetCurrentGame();

private:
    //=== ATTRIBUTES

    //Global
    int m_totalCoinsCollected;
    int m_totalDistance;
    int m_totalFlattenedEnemies;
    int m_totalGamesPlayed;
    std::string m_currentLanguage;
    std::string m_currentBallSkin;

    //Current Game
    int m_currentCoinsNumber;
    int m_currentDistance;
    int m_currentFlattenedEnemies;
    int m_currentScore;

    Leaderboard *m_leaderboard;

    std::set<std::string> m_activatedItemsArray;
};

#endif
