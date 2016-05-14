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
    updateActivatedItemsArray();
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
    @author Arthur  @date 2/05 - 14/05
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
vector<string> DataModel::getActivatedItemsArray() const { return m_activatedItemsArray; }


/********************************************
    Setters
*********************************************
    @author Arthur  @date 2/05 - 6/05
*********************************************/
void DataModel::setTotalCoinsCollected(int n) { m_totalCoinsCollected += n; }
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
    (Re)create files
*********************************************
    @author Arthur  @date 2/05 - 11/05
*********************************************/
void DataModel::createFile()
{
    fstream f;

    f.open( CONFIG_FILE.c_str(), ios::out);
    f << DEFAULT_CONFIG_CONTENT;
    f.close();

    f.open( HIDDEN_CONFIG_FILE.c_str(), ios::out);
    f << DEFAULT_CONFIG_CONTENT;
    f.close();
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
    Fetch Configuration data from file
*********************************************
    @author Arthur  @date 2/05 - 11/05
*********************************************/
void DataModel::fetchConfigurationFromFile()
{
    updateValue(m_totalCoinsCollected, "total_coins_collected");
    updateValue(m_totalDistance, "total_distance_travelled");
    updateValue(m_totalFlattenedEnemies, "total_enemies_destroyed");
    updateValue(m_totalGamesPlayed, "total_games_played");
    updateValue(m_currentLanguage, "language");

    updateActivatedItemsArray();
}


/********************************************
    Fetch Shop Items from file
*********************************************
    @author Arthur  @date 11/05 - 15/05
*********************************************/
void DataModel::fetchBuyableItemsFromFile(std::set<ShopItem*> &setArray)
{
    string result_value = "";
    string line="";
    string name = "";
    string desc = "";
    int price = 0;
    bool state = false;

    pugi::xml_document doc;
    doc.load_file("Resources/config.xml");

    pugi::xml_node shop = doc.child("runner").child("shop");

    for (pugi::xml_node item: shop.children("item"))
    {
        //update future item's attributes
        std::stringstream ss;
        name = item.attribute("name").value();
        desc = item.attribute("description").value();
        result_value = item.attribute("price").value();
        ss << result_value;
        ss >> price;
        result_value = item.attribute("boughtState").value();
        result_value == "true" ? state=true : state=false;

        //replace underscores by spaces
        for (unsigned int i=0; i < name.size(); i++)
                if (name[i] == '_') name[i] = ' ';
        for (unsigned int i=0; i < desc.size(); i++)
                if (desc[i] == '_') desc[i] = ' ';

        //add item to array
        setArray.insert ( new ShopItem(name, desc, price, state) );
    }
}


/********************************************
    Update variable value from file
*********************************************
    @author Arthur  @date 13/04 - 2/05
*********************************************/
template <typename Type>
void DataModel::updateValue(Type &variable, std::string name)
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
        found=line.find("name=\""+ name + "\"");
        if (found!=string::npos)
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
    ss >> variable;
}


/********************************************
    Update vector array of activated items
*********************************************
    @author Arthur  @date 14/05
*********************************************/
void DataModel::updateActivatedItemsArray()
{
    pugi::xml_document doc;
    doc.load_file("Resources/config.xml");

    pugi::xml_node runner = doc.child("runner");
    pugi::xml_node shop = runner.child("shop");

    for (pugi::xml_node item: shop.children("item"))
    {
        string tmp = item.attribute("boughtState").value();
        if ( tmp == "true")
            m_activatedItemsArray.push_back( item.attribute("name").value() );
    }
}


/********************************************
    Push Configuration data to file
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
