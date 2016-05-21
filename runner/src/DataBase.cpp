#include "../header/DataBase.h"

using namespace std;


/********************************************
    Default Constructor
*********************************************
    @author Arthur  @date 2/05
*********************************************/
DataBase::DataBase() :
    m_currentCoinsNumber{0}, m_currentDistance{0},
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
DataBase::~DataBase()
{
    delete m_leaderboard;
}

/*******************************************
    Getters
*********************************************
    @author Arthur  @date 2/05 - 14/05
*********************************************/
int DataBase::getTotalCoinsNumber() const { return m_totalCoinsCollected; }
int DataBase::getTotalDistance() const { return m_totalDistance; }
int DataBase::getTotalFlattenedEnemies() const { return m_totalFlattenedEnemies; }
int DataBase::getTotalGamesPlayed() const { return m_totalGamesPlayed; }
int DataBase::getCurrentCoinsNumber() const { return m_currentCoinsNumber; }
int DataBase::getCurrentDistance() const { return m_currentDistance; }
int DataBase::getCurrentFlattenedEnemies() const { return m_currentFlattenedEnemies; }
int DataBase::getCurrentScore() const { return m_currentScore; }
string DataBase::getLanguage() const { return m_currentLanguage;}
string DataBase::getBallSkin() const { return m_currentBallSkin; }
const set<string>& DataBase::getActivatedItemsArray() const { return m_activatedItemsArray; }


/********************************************
    Setters
*********************************************
    @author Arthur  @date 2/05 - 20/05
*********************************************/
void DataBase::setTotalCoinsCollected(int n) { m_totalCoinsCollected += n; }
void DataBase::setCurrentCoinsCollected(int n) { m_currentCoinsNumber += n; }
void DataBase::setCurrentDistance(int n) { m_currentDistance += n; }
void DataBase::setCurrentFlattenedEnemies(int n) { m_currentFlattenedEnemies += n; }
void DataBase::setLanguage(string lang) { m_currentLanguage = lang;}
void DataBase::setBallSkin(string skin) { m_currentBallSkin = skin; }
void DataBase::setCurrentScore(float speed)
{
    m_currentScore = ( speed*m_currentDistance
            + 20*m_currentCoinsNumber + m_currentFlattenedEnemies );
}


/********************************************
    (Re)create files
*********************************************
    @author Arthur  @date 2/05 - 11/05
*********************************************/
void DataBase::createFile()
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
bool DataBase::checkFileIntegrity()
{
    fstream f1;
    fstream f2;
    string f1Line;
    string f2Line;

    //=== Open files / create them if not existing

    f1.open( CONFIG_FILE.c_str(), ios::in);
    f2.open( HIDDEN_CONFIG_FILE.c_str(), ios::in);

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
                return false; //lines are different
            }
            if ( f1Line == "") //both are empty (checked before difference)
            {
                f1.close();
                f2.close();
                return false; //lines shouldn't be empty
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
    @author Arthur  @date 2/05 - 20/05
*********************************************/
void DataBase::fetchConfigurationFromFile()
{
    updateValue(m_totalCoinsCollected, "total_coins_collected");
    updateValue(m_totalDistance, "total_distance_travelled");
    updateValue(m_totalFlattenedEnemies, "total_enemies_destroyed");
    updateValue(m_totalGamesPlayed, "total_games_played");
    updateValue(m_currentLanguage, "language");
    updateValue(m_currentBallSkin, "ball_skin");

    updateActivatedItemsArray();
}


/********************************************
    Fetch Shop Items from file
*********************************************
    @author Arthur  @date 11/05 - 18/05
*********************************************/
void DataBase::fetchBuyableItemsFromFile(vector<ShopItem*> &setArray)
{
    string result_value = "";
    string name = "";
    string desc = "";
    int price = 0;

    //open file with pugi library and init nodes
    pugi::xml_document doc;
    doc.load_file("Resources/config.xml");

    pugi::xml_node shop = doc.child("runner").child("shop");

    for (pugi::xml_node item: shop.children("item"))
    {
        //update item's attributes
        bool state = false;
        std::stringstream ss;
        name = item.attribute("name").value();
        desc = item.attribute("description").value();
        result_value = item.attribute("price").value();
        ss << result_value;
        ss >> price;
        result_value = item.attribute("boughtState").value();
        if (result_value == "true" ) state=true;

        //add item to array
        setArray.push_back( new ShopItem(name, desc, price, state) );
    }
}


/********************************************
    Update variable value from file
*********************************************
    @author Arthur  @date 13/04 - 2/05
*********************************************/
template <typename Type>
void DataBase::updateValue(Type &variable, std::string name)
{
    fstream f;
    size_t found = string::npos;
    string result = "";
    string line="";

    f.open(CONFIG_FILE, ios::in);

    assert( !f.fail());
    /* look for the line containing the name parameter
    * then update in this line the area between brackets
    */
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
    @author Arthur  @date 14/05 - 21/05
*********************************************/
void DataBase::updateActivatedItemsArray()
{
    pugi::xml_document doc;
    doc.load_file("Resources/config.xml");

    pugi::xml_node runner = doc.child("runner");
    pugi::xml_node shop = runner.child("shop");

    for (pugi::xml_node item: shop.children("item"))
    {
        string tmp = item.attribute("boughtState").value();
        if ( tmp == "true")
            m_activatedItemsArray.insert( item.attribute("id").value() );
    }
}


/********************************************
    Push Configuration data to file
*********************************************
    @author Arthur  @date 2/05 - 20/05
*********************************************/
void DataBase::pushConfigurationToFile()
{
    fstream f1;
    fstream f2;
    string line = "";

    //=== replace by variables values

    f1.open(CONFIG_FILE, ios::in);
    f2.open(HIDDEN_CONFIG_FILE, ios::out);

    if (f1.fail() || f2.fail() )
        createFile();

    /* for each line, compare to the read only file and rewrite it the same
    * except when condition are granted. In that case replace elements of lines
    * with variables value and add the closing tag
    */

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
        else if (line.find("ball_skin") !=std::string::npos)
        {
            line.replace(line.begin() + line.find('>')+1, line.end(), m_currentBallSkin);
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
void DataBase::saveCurrentGame()
{
    //add current game values to total values
    m_totalCoinsCollected += m_currentCoinsNumber;
    m_totalDistance += m_currentDistance;
    m_totalFlattenedEnemies += m_currentFlattenedEnemies;

    //update leaderboard
    m_leaderboard->loadVectorFromFile();
    m_leaderboard->addEntryToVector(m_currentScore);
    m_leaderboard->loadFileFromVector();
}


/********************************************
    Reset Current Game
*********************************************
    @author Arthur  @date 2/05
*********************************************/
void DataBase::resetCurrentGame()
{
    //for launching a new game
    m_totalGamesPlayed += 1;
    m_currentCoinsNumber = 0;
    m_currentDistance = 0;
    m_currentFlattenedEnemies = 0;
    m_currentScore = 0;
}
