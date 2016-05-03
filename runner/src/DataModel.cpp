#include "../header/DataModel.h"

using namespace std;


/********************************************
    Default Constructor
*********************************************
    @author Arthur  @date 2/05
*********************************************/
DataModel::DataModel() :
    m_currentCoinsCollected{0}, m_currentDistance{0},
    m_currentEnemyDestructed{0}, m_currentScore{0}
{
    if ( checkFileIntegrity() == false)
        createFile();
    fetchConfigurationFromFile();
    m_leaderboard = new Leaderboard;
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 2/05
*********************************************/
DataModel::~DataModel()
{
    delete m_leaderboard;
}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 2/05
*********************************************/
int DataModel::getTotalCoinsCollected() const { return m_totalCoinsCollected; }
int DataModel::getTotalDistanceTravelled() const { return m_totalDistance; }
int DataModel::getTotalEnemiesDestructed() const { return m_totalEnemiesDestructed; }
int DataModel::getTotalGamesPlayed() const { return m_totalGamesPlayed; }
int DataModel::getCurrentCoinsCollected() const { return m_currentCoinsCollected; }
int DataModel::getCurrentDistance() const { return m_currentDistance; }
int DataModel::getCurrentEnemyDestructed() const { return m_currentEnemyDestructed; }
int DataModel::getCurrentScore() const { return m_currentScore; }


/********************************************
    Setters
*********************************************
    @author Arthur  @date 2/05
*********************************************/
void DataModel::setCurrentCoinsCollected(int n) { m_currentCoinsCollected += n; }
void DataModel::setCurrentDistance(int n) { m_currentDistance += n; }
void DataModel::setCurrentEnemiesDestructed(int n) { m_currentEnemyDestructed += n; }
void DataModel::setCurrentScore(float speed, int difficulty)
{
    m_currentScore = ( (speed+2*difficulty)*m_currentDistance
            + 20*m_currentCoinsCollected + m_currentEnemyDestructed );
}

/********************************************
    Fetch Configuration data from file
*********************************************
    @author Arthur  @date 2/05
*********************************************/
void DataModel::fetchConfigurationFromFile()
{
    updateInt(m_totalCoinsCollected, "total_coins_collected");
    updateInt(m_totalDistance, "total_distance_travelled");
    updateInt(m_totalEnemiesDestructed, "total_enemies_destroyed");
    updateInt(m_totalGamesPlayed, "total_games_played");
}

void DataModel::updateInt(int &currentVariable, string currentName)
{
    fstream f;
    size_t found = string::npos;
    string result = "";
    string line="";

    f.open(CONFIG_FILE, ios::in);
    assert( !f.fail() );

    f >> line;
    while( !f.eof() && found == string::npos)
    {
        found=line.find("name=\""+ currentName + "\"");
        if (found!=std::string::npos)
        {
            int pos = 0;
            while ( line[pos] != '>') pos++;
            pos++;
            while ( line[pos] != '<')
            {
                result += line[pos];
                pos++;
            }
            for (unsigned int i=0; i < result.size(); i++)
                if (result[i] == '_') result[i] = ' ';
        }
        f >> line;
    }

    f.close();

    currentVariable = stoi(result);
}

/********************************************
    Fetch Configuration data from file
*********************************************
    @author Arthur  @date 2/05
*********************************************/
void DataModel::pushConfigurationToFile()
{
    fstream f1;
    fstream f2;
    string line = "";

    //=== replace by variables values

    f1.open(CONFIG_FILE, ios::in);
    f2.open(HIDDEN_CONFIG_FILE, ios::out);

    if (f1.fail() || f2.fail() )
        createFile();

    getline(f1, line, '\n');
    while ( !f1.eof())
    {
        if (line.find("total_coins_collected") !=std::string::npos)
        {
            line.replace(line.begin() + line.find('>')+1, line.begin() + line.find('<'),
                         to_string(m_totalCoinsCollected));
            line += "</int>";
        }
        else if (line.find("total_enemies_destroyed") !=std::string::npos)
        {
            line.replace(line.begin() + line.find('>')+1, line.begin() + line.find('<'),
                         to_string(m_totalEnemiesDestructed));
            line += "</int>";
        }
        else if (line.find("total_distance_travelled") !=std::string::npos)
        {
            line.replace(line.begin() + line.find('>')+1, line.begin() + line.find('<'),
                         to_string(m_totalDistance));
            line += "</int>";
        }
        else if (line.find("total_games_played") !=std::string::npos)
        {
            line.replace(line.begin() + line.find('>')+1, line.end(),
                         to_string(m_totalGamesPlayed));
            line += "</int>";
        }

        line += "\n";
        f2 << line;
        getline(f1, line, '\n');
    }

    f1.close();
    f2.close();

    //=== Copy second file

    f1.open(HIDDEN_CONFIG_FILE, ios::in);
    f2.open(CONFIG_FILE, ios::out);

    if (f1.fail() || f2.fail() )
        createFile();

    getline(f1, line, '\n');
    while ( !f1.eof())
    {
        line += "\n";
        f2 << line;
        getline(f1, line, '\n');
    }

    f1.close();
    f2.close();

}


/********************************************
    Reset Current Game
*********************************************
    @author Arthur  @date 2/05
*********************************************/
void DataModel::resetCurrentGame()
{
    m_totalGamesPlayed += 1;
    m_currentCoinsCollected = 0;
    m_currentDistance = 0;
    m_currentEnemyDestructed = 0;
    m_currentScore = 0;
}


/********************************************
    Save Current Game
*********************************************
    @author Arthur  @date 2/05
*********************************************/
void DataModel::saveCurrentGame()
{
    m_totalCoinsCollected += m_currentCoinsCollected;
    m_totalDistance += m_currentDistance;
    m_totalEnemiesDestructed += m_currentEnemyDestructed;

    m_leaderboard->loadVectorFromFile();
    m_leaderboard->addEntryToVector(m_currentScore);
    m_leaderboard->loadFileFromVector();
}

/********************************************
    Check if someone has changed one file
*********************************************
    @author Arthur  @date 2/05
*********************************************/
bool DataModel::checkFileIntegrity()
{
    fstream f1;
    fstream f2;
    string f1Line;
    string f2Line;

    f1.open( CONFIG_FILE.c_str(), ios::in);
    f2.open( HIDDEN_CONFIG_FILE.c_str(), ios::in);

    if ( f1.fail() || f2.fail() )
        createFile();
    else
    {
        do
        {
            f1 >> f1Line;
            f2 >> f2Line;
            if ( f1Line != f2Line)
            {
                f1.close();
                f2.close();
                return false;
            }
            if ( f1Line == "")
            {
                f1.close();
                f2.close();
                return false;
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
    @author Arthur  @date 2/05
*********************************************/
void DataModel::createFile()
{
    fstream f;

    f.open( CONFIG_FILE.c_str(), ios::out);
    f << "<?xml version='1.0' encoding='utf-8'?>\n";
    f << "<runner>\n";
    f << "    <stats>\n";
    f << "    	<int name=\"total_coins_collected\">0</int>\n";
    f << "    	<int name=\"total_distance_travelled\">0</int>\n";
    f << "    	<int name=\"total_enemies_destroyed\">0</int>\n";
    f << "    	<int name=\"total_games_played\">0</int>\n";
    f << "    </stats>\n";
    f << "   <shop>\n";
    f << "    	<boolean name=\"double_coin_bought\" value=\"false\" />\n";
    f << "   </shop>\n";
    f << "</runner>\n";

    f.close();

    f.open( HIDDEN_CONFIG_FILE.c_str(), ios::out);
    f << "<?xml version='1.0' encoding='utf-8'?>\n";
    f << "<runner>\n";
    f << "    <stats>\n";
    f << "    	<int name=\"total_coins_collected\">0</int>\n";
    f << "    	<int name=\"total_distance_travelled\">0</int>\n";
    f << "    	<int name=\"total_enemies_destroyed\">0</int>\n";
    f << "    	<int name=\"total_games_played\">0</int>\n";
    f << "    </stats>\n";
    f << "   <shop>\n";
    f << "    	<boolean name=\"double_coin_bought\" value=\"false\" />\n";
    f << "   </shop>\n";
    f << "</runner>\n";
    f.close();
}
