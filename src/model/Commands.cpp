#include "Commands.h"

using namespace std;

/**
 * Constructs a Commands model with database
 * @author Arthur
 * @date 24/01/17
 *
 * @param dataBase the common app's dataBase
 */
Commands::Commands(DataBase *dataBase) :  m_dataBase{dataBase}
{}


/**
 * Destructor
 * @author Arthur
 * @date 24/01/17
 */
Commands::~Commands() = default;


//=== Getters
DataBase* Commands::getDataBase() const { return m_dataBase; }
