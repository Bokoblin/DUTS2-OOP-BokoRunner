#include "TestCore.h"

namespace ModelResources = Bokoblin::BokoRunner::Resources::Model;

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

//FIXME: ALL THOSE CONFIGS ARE LINKED TO FILE BASED, WE SHALL ABSTRACT THAT ALSO
std::string TestCore::getPersistenceContext() const { return "test_config.xml"; }
