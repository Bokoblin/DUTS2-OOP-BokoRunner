#include "../header/DataModel.h"

using namespace std;


/********************************************
    Default Constructor
*********************************************
    @author Arthur  @date 2/05
*********************************************/
DataModel::DataModel() :
    m_currentCoinsCollected{0}, m_currentDistance{0},
    m_currentFlattenedEnemies{0}, m_currentScore{0}
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
    @author Arthur  @date 2/05 - 6/05
*********************************************/
int DataModel::getTotalCoinsCollected() const { return m_totalCoinsCollected; }
int DataModel::getTotalDistanceTravelled() const { return m_totalDistance; }
int DataModel::getTotalEnemiesDestructed() const { return m_totalFlattenedEnemies; }
int DataModel::getTotalGamesPlayed() const { return m_totalGamesPlayed; }
int DataModel::getCurrentCoinsCollected() const { return m_currentCoinsCollected; }
int DataModel::getCurrentDistance() const { return m_currentDistance; }
int DataModel::getCurrentFlattenedEnemies() const { return m_currentFlattenedEnemies; }
int DataModel::getCurrentScore() const { return m_currentScore; }
string DataModel::getLanguage() const {return m_currentLanguage;}


/********************************************
    Setters
*********************************************
    @author Arthur  @date 2/05 - 6/05
*********************************************/
void DataModel::setCurrentCoinsCollected(int n) { m_currentCoinsCollected += n; }
void DataModel::setCurrentDistance(int n) { m_currentDistance += n; }
void DataModel::setCurrentFlattenedEnemies(int n) { m_currentFlattenedEnemies += n; }
void DataModel::setLanguage(string lang) { m_currentLanguage = lang;}
void DataModel::setCurrentScore(float speed)
{
    m_currentScore = ( speed*m_currentDistance
            + 20*m_currentCoinsCollected + m_currentFlattenedEnemies );
}

/********************************************
    Fetch Configuration data from file
*********************************************
    @author Arthur  @date 2/05 - 6/05
*********************************************/
void DataModel::fetchConfigurationFromFile()
{
    updateValue(m_totalCoinsCollected, "total_coins_collected");
    updateValue(m_totalDistance, "total_distance_travelled");
    updateValue(m_totalFlattenedEnemies, "total_enemies_destroyed");
    updateValue(m_totalGamesPlayed, "total_games_played");
    updateValue(m_currentLanguage, "language");
}

template <typename Type>
void DataModel::updateValue(Type &currentVariable, string currentName)
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

    std::stringstream ss;
    ss << result;
    ss >> currentVariable;
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
                         to_string(m_totalFlattenedEnemies));
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
        else if (line.find("language") !=std::string::npos)
        {
            line.replace(line.begin() + line.find('>')+1, line.end(), m_currentLanguage);
            line += "</string>";
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
    m_currentFlattenedEnemies = 0;
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
    m_totalFlattenedEnemies += m_currentFlattenedEnemies;

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
    @author Arthur  @date 2/05 - 6/05
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
    f << "    <config>\n";
    f << "    <string name=\"language\">en</string>\n";
    f << "    </config>\n";
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
    f << "    <config>\n";
    f << "    <string name=\"language\">en</string>\n";
    f << "    </config>\n";
    f << "</runner>\n";
    f.close();
}
