#include "Leaderboard.h"

using namespace std;

/**
 * Default Constructor
 * @author Arthur
 * @date 19/04 - 24/10
 */
Leaderboard::Leaderboard(DataBase *data) :  m_dataBase{data}
{}

/**
 * Destructor
 * @author Arthur
 * @date 19/04
 */
Leaderboard::~Leaderboard() {}


//=== Getters

DataBase *Leaderboard::getDataBase() const { return m_dataBase; }