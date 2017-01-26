#include "Leaderboard.h"

using namespace std;

/**
 * Constructs a Leaderboard model with database
 * @author Arthur
 * @date 19/04/16 - 24/10/16
 *
 * @param dataBase the common app's dataBase
 */
Leaderboard::Leaderboard(DataBase *dataBase) :  m_dataBase{dataBase}
{}

/**
 * Destructor
 * @author Arthur
 * @date 19/04/16
 */
Leaderboard::~Leaderboard() {}


//=== Getters

DataBase *Leaderboard::getDataBase() const { return m_dataBase; }