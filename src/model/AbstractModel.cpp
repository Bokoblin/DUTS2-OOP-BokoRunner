#include "AbstractModel.h"

/**
 * Parameterized Constructor called
 * by the inherited classes
 * @author Arthur, Florian
 * @date 21/02 - 26/12
 */
AbstractModel::AbstractModel(DataBase *dataBase) : m_dataBase{dataBase}
{}

/**
 * Copy Constructor
 * @author Arthur
 * @date 14/04 - 20/12
 */
AbstractModel::AbstractModel(const AbstractModel& model) :
        m_dataBase{model.m_dataBase}
{}

/**
 * Destructor
 * @author Arthur, Florian
 * @date 21/02 - 26/03
 */
AbstractModel::~AbstractModel() {}


//=== Getters
DataBase *AbstractModel::getDataBase() const
{
    return m_dataBase;
}


