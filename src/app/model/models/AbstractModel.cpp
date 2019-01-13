#include "AbstractModel.h"

/**
 * Parameterized Constructor called
 * by the inherited classes
 * @author Arthur, Florian
 * @date 21/02/16 - 29/01/17
 *
 * @param appCore the app's core singleton
 */
AbstractModel::AbstractModel(AppCore* appCore) : m_appCore{appCore}
{}


/**
 * Destructor
 * @author Arthur, Florian
 * @date 21/02/16 - 26/03/16
 */
AbstractModel::~AbstractModel() = default;


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void AbstractModel::setAppState(const AppState& state)
{
    m_appCore->setAppState(state);
}
