#include "../header/Leaderboard.h"

using namespace std;


/********************************************
    Default Constructor
*********************************************
    @author Arthur  @date 19/04 - 2/05
*********************************************/
Leaderboard::Leaderboard() : m_scoresArray{}
{ }


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

    f.open(SCORES_FILE.c_str(), ios::in);

    if (f.fail() )
        createFile(); //create an empty file if file doesn't exist

    f >> line;
    while ( !f.eof() )
    {
        //transform each line in int and add it to vector array
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

    f1.open( SCORES_FILE.c_str(), ios::out);
    f2.open( HIDDEN_SCORES_FILE.c_str(), ios::out);
    if (f1.fail() || f2.fail() )
        createFile();

    //=== Write vector elements in files

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

    //=== keep only a certain number of scores

    while (m_scoresArray.size() > MAX_SCORES)
        m_scoresArray.pop_back();
}


/********************************************
    Indicate the way to sort array
*********************************************
    @author Arthur  @date 19/04
*********************************************/
void Leaderboard::addEntryToVector(int new_score)
{
    //add new score to vector, then sort it
    m_scoresArray.push_back(new_score);
    sortVector();
}


/********************************************
    fetch string content with the vector
*********************************************
    @author Arthur  @date 19/04 - 20/04
*********************************************/
void Leaderboard::loadStringFromVector(std::string &scores_text)
{
    if ( m_scoresArray.empty() == false)
    {
        //add each case content in string
        for (vector<int>::iterator it = m_scoresArray.begin();
             it != m_scoresArray.end(); ++it)
            scores_text += " \n " + to_string(*it);
    }
    else
        scores_text = "empty"; //if array is empty
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

    f1.open( SCORES_FILE.c_str(), ios::in);
    f2.open( HIDDEN_SCORES_FILE.c_str(), ios::in);

    if ( f1.fail() || f2.fail() )
        createFile();
    else
    {
        /* check if one of the files has been changed
         * Note: is useless if the user knows the 2 files
         * and write the same thing in both
         */

        do {
            f1 >> f1Line;
            f2 >> f2Line;
            if ( f1Line != f2Line)
            {
                f1.close();
                f2.close();
                return false;//lines are different
            }
        }
        while ( !f1.eof() );
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

    f.open( SCORES_FILE.c_str(), ios::out);
    f << "";
    f.close();

    f.open( HIDDEN_SCORES_FILE.c_str(), ios::out);
    f << "";
    f.close();
}
