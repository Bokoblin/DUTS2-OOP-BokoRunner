/* Copyright 2016-2017 Jolivet Arthur & Laronze Florian

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

#ifndef DATABASE_H
#define DATABASE_H

#include "../../libs/pugixml-1.8/src/pugixml.hpp"
#include <iostream>
#include <cassert>
#include <set>
#include <fstream>
#include "../constants.h"

enum Difficulty
{
    EASY = 1,
    HARD = 2
};


/**
 * DataBase Class
 * @author Arthur
 * @date 2/05/16 - 07/01/17
 */
class DataBase
{
public:
    //=== CTORs / DTORs
    DataBase();
    DataBase(const DataBase& d)=delete;

    //=== GETTERS
    int getTotalCoinsNumber() const;
    int getTotalDistance() const;
    int getTotalFlattenedEnemies() const;
    int getTotalGamesPlayed() const;
    int getCurrentCoinsNumber() const;
    int getCurrentDistance() const;
    int getCurrentFlattenedEnemies() const;
    int getCurrentScore() const;
    int getWallet() const;
    int getDifficulty() const;
    std::string getLanguage() const;
    std::string getBallSkin() const;
    const std::set<std::string>& getActivatedItemsArray() const;
    std::string getLanguageFile() const;

    //=== SETTERS
    void decreaseWallet(int amount);
    void increaseCurrentCoinsCollected(int amount);
    void increaseCurrentDistance(float amount);
    void increaseCurrentFlattenedEnemies(int amount);
    void setCurrentScore(float speed);
    void setDifficulty(int difficulty);
    void setLanguage(std::string lang);
    void setBallSkin(std::string skin);

    //=== METHODS
    void createFile();
    bool checkFileIntegrity();
    void fetchConfigurationFromFile();
    std::string getStringFromFile(std::string description);
    void updateConfigValues();
    void updateActivatedItemsArray();
    void updateScoreArray();
    void pushConfigurationToFile();
    void addEntryToScoreArray(int new_score);
    void loadStringFromArray(std::string &scores_text);
    void saveCurrentGame();
    void launchNewGame();
    void resetScore();
    void clearAppData();

private:
    //=== ATTRIBUTES
    //Global App
    int m_totalCoinsCollected;
    int m_totalDistance;
    int m_totalFlattenedEnemies;
    int m_totalGamesPlayed;
    int m_wallet;
    int m_currentDifficulty;
    std::string m_currentLanguage;
    std::string m_currentBallSkin;
    const int COIN_MULTIPLIER = 20;
    const int MAX_SCORES = 10;

    //Current Game
    int m_currentCoinsNumber;
    float m_currentDistance;
    int m_currentFlattenedEnemies;
    int m_currentScore;

    //Containers
    std::set<int> m_scoresArray;
    std::set<std::string> m_activatedItemsArray;
};

#endif
