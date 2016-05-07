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

/********************************************
    Leaderboard Class
*********************************************
    @author Arthur  @date  19/04 - 2/05
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

#endif // LEADERBOARD_H
