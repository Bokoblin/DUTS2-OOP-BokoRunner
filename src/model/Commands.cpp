#include "Commands.h"

/**
 * Constructs a Commands model with database
 * @author Arthur
 * @date 24/01/17 - 30/01/17
 *
 * @param dataBase the common app's dataBase
 */
Commands::Commands(DataBase *dataBase) :
        AbstractModel{dataBase}
{}


/**
 * Destructor
 * @author Arthur
 * @date 24/01/17
 */
Commands::~Commands()
{}

/**
 * Next Step
 * @author Arthur
 * @date 30/01/17
 */
void Commands::nextStep()
{}