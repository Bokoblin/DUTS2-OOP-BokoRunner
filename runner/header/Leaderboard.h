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

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

/********************************************
    Constant Variables
********************************************/
const std::string SCORES_FILE = "Resources/scores.txt";
const std::string HIDDEN_SCORES_FILE = "Resources/.font_cache";
//hidden in linux and not explicit to score
const int MAX_SCORES = 10;

/********************************************
    Leaderboard Class
*********************************************
    @author Arthur  @date  19/04 - 21/05
*********************************************/
class Leaderboard
{
public:
    //=== CTORs / DTORs
    Leaderboard();
    ~Leaderboard();

    //=== METHODS
    void createFile();
    void loadVectorFromFile();
    void loadFileFromVector();
    void sortVector();
    void addEntryToVector(int new_score);
    void loadStringFromVector(std::string &scores_text);
    bool checkFileIntegrity();

private:
    std::vector<int> m_scoresArray;

};

#endif
