#include "AbstractModel.h"

/**
 * Parameterized Constructor called
 * by the inherited classes
 * @author Arthur, Florian
 * @date 21/02/16 - 29/01/17
 *
 * @param dataBase the app's dataBase
 */
AbstractModel::AbstractModel(DataBase *dataBase) : m_dataBase{dataBase}
{}


/**
 * Destructor
 * @author Arthur, Florian
 * @date 21/02/16 - 26/03/16
 */
AbstractModel::~AbstractModel() = default;


//=== Getters

DataBase *AbstractModel::getDataBase() const { return m_dataBase; }
