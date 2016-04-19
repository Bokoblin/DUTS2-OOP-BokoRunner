#include "Leaderboard.h"

using namespace std;


/********************************************
    Default Constructor
*********************************************
    @author Arthur  @date 19/04 - 20/04
*********************************************/
Leaderboard::Leaderboard() : m_scoresArray{}
{
    m_file = "scores.txt";
    m_hiddenFile = "header/.old_lib_files.hpp";
    //hidden in linux and not explicit to score
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 19/04
*********************************************/
Leaderboard::~Leaderboard()
{ }


/********************************************
    load scores in vector
*********************************************
    @author Arthur  @date 19/04
*********************************************/
void Leaderboard::loadVectorFromFile()
{
    fstream f;
    string line="";

    m_scoresArray.clear();

    f.open(m_file.c_str(), ios::in);

    if (f.fail() )
        createFile();

    f >> line;
    while ( !f.eof() )
    {
        m_scoresArray.push_back(stoi( line ));
        f >> line;
    }

    f.close();
}


/********************************************
    load scores file from Vector
*********************************************
    @author Arthur  @date 19/04 - 20/04
*********************************************/
void Leaderboard::loadFileFromVector()
{
    fstream f1;
    fstream f2;

    f1.open( m_file.c_str(), ios::out);
    f2.open( m_hiddenFile.c_str(), ios::out);
    if (f1.fail() || f2.fail() )
        createFile();

    for (vector<int>::iterator it = m_scoresArray.begin();
         it != m_scoresArray.end(); ++it)
    {
        f1 << to_string(*it) << endl;
        f2 << to_string(*it) << endl;
    }

    f1.close();
    f2.close();
}



/********************************************
    Indicate the way to sort array
*********************************************
    @author Arthur  @date 19/04
*********************************************/
bool wayToSort(int i, int j) { return i > j; }


/********************************************
    Indicate the way to sort array
*********************************************
    @author Arthur  @date 19/04
*********************************************/
void Leaderboard::sortVector()
{
    //=== Sort array

    sort( m_scoresArray.begin(), m_scoresArray.end(), wayToSort );

    //=== keep only 10 scores

    while (m_scoresArray.size() > 10)
        m_scoresArray.pop_back();
}


/********************************************
    Indicate the way to sort array
*********************************************
    @author Arthur  @date 19/04
*********************************************/
void Leaderboard::addEntryToVector(int new_score)
{
    m_scoresArray.push_back(new_score);
    sortVector();
}


/********************************************
    Indicate the way to sort array
*********************************************
    @author Arthur  @date 19/04
*********************************************/
void Leaderboard::loadStringFromVector(std::string &scores_text, string language)
{
    if ( m_scoresArray.empty() == true)
    {
        if ( language == "en")
            scores_text = "There isn't any score yet";
        else if ( language == "fr")
            scores_text = "Il n'y a pas encore de scores";
        else if ( language == "es")
            scores_text = "Todavia no hay ninguna puntuacion";
    }
    else
    {
        scores_text = "";
        for (vector<int>::iterator it = m_scoresArray.begin();
             it != m_scoresArray.end(); ++it)
            scores_text += " \n " + to_string(*it);
    }
}


/********************************************
    Check if someone has changed one file
*********************************************
    @author Arthur  @date 19/04 - 20/04
*********************************************/
bool Leaderboard::checkFileIntegrity()
{
    fstream f1;
    fstream f2;
    string f1Line;
    string f2Line;

    f1.open( m_file.c_str(), ios::in);
    f2.open( m_hiddenFile.c_str(), ios::in);

    if ( f1.fail() || f2.fail() )
        createFile();
    else
    {
        /* check if one of the files has been changed
         * does not work if the player knows the 2 files
         * and write the same thing in both
         */

        f1 >> f1Line;
        f2 >> f2Line;

        while ( !f1.eof() || !f2.eof() )
        {
            if ( f1Line != f2Line)
            {
                f1.close();
                f2.close();
                return false;
            }
            else
            {
                f1 >> f1Line;
                f2 >> f2Line;
            }
        }
    }

    f1.close();
    f2.close();

    return true;
}


/********************************************
    (Re)create files
*********************************************
    @author Arthur  @date 19/04
*********************************************/
void Leaderboard::createFile()
{
    /**< also use to reset files */

    fstream f;

    f.open( m_file.c_str(), ios::out);
    f << "";
    f.close();

    f.open( m_hiddenFile.c_str(), ios::out);
    f << "";
    f.close();
}
