#include "Leaderboard.h"

using namespace std;

/**
 * Default Constructor
 * @author Arthur
 * @date 19/04 - 26/12
 */
Leaderboard::Leaderboard(DataBase *dataBase) :
        AbstractModel(dataBase)
{}

/**
 * Destructor
 * @author Arthur
 * @date 19/04
 */
Leaderboard::~Leaderboard() {}

/**
 * Next Step
 * @author Arthur
 * @date 27/12
 */
void Leaderboard::nextStep()
{
    if (!m_dataBase->checkFileIntegrity())
        m_dataBase->createFile();
}