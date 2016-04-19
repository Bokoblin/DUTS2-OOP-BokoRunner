#include "../header/MenuModel.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 14/04
*********************************************/
MenuModel::MenuModel(const Model& model) :
    Model(model), m_homeState{true}, m_settingsState{false}
{}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 14/04
*********************************************/
MenuModel::~MenuModel()
{}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 14/04
*********************************************/
bool MenuModel::getHomeState() const
{
    return m_homeState;
}
bool MenuModel::getSettingsState() const
{
    return m_settingsState;
}


/********************************************
    Setters
*********************************************
    @author Arthur  @date 14/04
*********************************************/
void MenuModel::setHomeState(bool state)
{
    m_homeState = state;
}
void MenuModel::setSettingsState(bool state)
{
    m_settingsState = state;
}


/********************************************
    Next Step
*********************************************
    @author Arthur  @date 14/04
*********************************************/
void MenuModel::nextStep()
{

}


/********************************************
    Load Leaderboard on console from file
*********************************************
    @author Arthur  @date 19/04
*********************************************/
void MenuModel::loadLeaderboard(string file)
{
    fstream f;
    string line="";

    f.open(file.c_str(), ios::in);
    assert( !f.fail() );

    f >> line;
    while( !f.eof())
    {
        cout << line << endl;
        f >> line;
    }
    cout << endl;

    f.close();
}


/********************************************
    Indicate the way to sort array
*********************************************
    @author Arthur  @date 19/04
*********************************************/
bool wayToSort(int i, int j) { return i > j; }



/********************************************
    Sort Leaderboard and write file
*********************************************
    @author Arthur  @date 19/04
*********************************************/
void MenuModel::sortLeaderboard(string file)
{
    fstream f;
    string line="";
    vector <int> scoresVec;

    //=== Full an int array with a file

    f.open(file.c_str(), ios::in);
    assert( !f.fail() );

    f >> line;
    while ( !f.eof() )
    {
        scoresVec.push_back(stoi( line ));
        f >> line;
    }

    f.close();


    //=== Sort array and keep only 10 scores

    sort( scoresVec.begin(), scoresVec.end(), wayToSort );

    while (scoresVec.size() > 10) scoresVec.pop_back();


    //=== Write sorted array in file

    f.open( file.c_str(), ios::out);
    assert (!f.fail() );

    for (vector<string>::size_type i = 0; i != scoresVec.size(); ++i)
        f << to_string(scoresVec[i]) << endl;

    f.close();
}
