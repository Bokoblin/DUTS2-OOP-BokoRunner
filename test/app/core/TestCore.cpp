#include "TestCore.h"

//------------------------------------------------
//          CONSTRUCTOR / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs the test core
 *
 * @author Arthur
 * @date 25/08/18
 */
TestCore::TestCore() : AppCore()
{}


/**
 * Destructor
 * @author Arthur
 * @date 25/08/18
 */
TestCore::~TestCore() = default;


//------------------------------------------------
//          GETTERS
//------------------------------------------------

std::string TestCore::getConfigFile() const { return TEST_CONFIG_FILE; }
