#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

    std::string m_file;
    std::string m_hiddenFile;

};

#endif // LEADERBOARD_H
