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

#ifndef _DATAMODEL_H
#define _DATAMODEL_H

#include "Leaderboard.h"
#include <iostream>
#include <fstream>
#include <cassert>

/********************************************
    Constant Variables
********************************************/
//GAME
const std::string CONFIG_FILE = "Resources/config.xml";
const std::string HIDDEN_CONFIG_FILE = "Resources/.temp.xml";

/********************************************
    DataModel Class
*********************************************
    @author Arthur  @date 2/05 - 3/05
*********************************************/
class DataModel
{
public:
    //=== CTORs / DTORs
    DataModel();
    ~DataModel();

    //=== GETTERS
    int getTotalCoinsCollected() const;
    int getTotalDistanceTravelled() const;
    int getTotalEnemiesDestructed() const;
    int getTotalGamesPlayed() const;
    int getCurrentCoinsCollected() const;
    int getCurrentDistance() const;
    int getCurrentEnemyDestructed() const;
    int getCurrentScore() const;

    //=== SETTERS
    void setCurrentCoinsCollected(int number);
    void setCurrentDistance(int number);
    void setCurrentEnemiesDestructed(int number);
    void setCurrentScore(float speed, int difficulty);

    //=== METHODS
    void fetchConfigurationFromFile();
    void pushConfigurationToFile();
    void saveCurrentGame();
    void resetCurrentGame();
    void createFile();
    bool checkFileIntegrity();
    void updateInt(int &variable, std::string name);


private:
    //=== ATTRIBUTES

    //Global
    int m_totalCoinsCollected;
    int m_totalDistance;
    int m_totalEnemiesDestructed;
    int m_totalGamesPlayed;

    //Current Game
    int m_currentCoinsCollected;
    int m_currentDistance;
    int m_currentEnemyDestructed;
    int m_currentScore;

    Leaderboard *m_leaderboard;

    //Containers
    //std::vector<std::string> m_ItemsUnlockedArray; //for next dev

};

#endif
