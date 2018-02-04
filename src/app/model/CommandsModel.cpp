#include "CommandsModel.h"

/**
 * Constructs a Commands model with app core
 * @author Arthur
 * @date 24/01/17 - 30/01/17
 *
 * @param appCore the app's core singleton
 */
CommandsModel::CommandsModel(AppCore *appCore) :
        AbstractModel{appCore}
{}


/**
 * Destructor
 * @author Arthur
 * @date 24/01/17
 */
CommandsModel::~CommandsModel() = default;


/**
 * Next Step
 * @author Arthur
 * @date 30/01/17
 */
void CommandsModel::nextStep()
{}
