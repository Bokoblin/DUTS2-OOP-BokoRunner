#include "Commands.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 24/01/17
 */
Commands::Commands(DataBase *dataBase) :  m_dataBase{dataBase}
{}


/**
 * Destructor
 * @author Arthur
 * @date 24/01/17
 */
Commands::~Commands()
{}


//=== Getters
DataBase* Commands::getDataBase() const { return m_dataBase; }
