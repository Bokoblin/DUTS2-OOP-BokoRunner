#include "LocalizationManager.h"

using std::string;
using Bokoblin::SimpleLogger::Logger;

//------------------------------------------------
//          STATIC MEMBERS
//------------------------------------------------

bool LocalizationManager::m_isInit = false;
AppCore* LocalizationManager::m_appCore = nullptr;

//------------------------------------------------
//          PUBLIC METHODS
//------------------------------------------------

/**
 * Inits the app persistence manager context
 * and the persistence system
 *
 * @author Arthur
 * @date 04/02/17
 */
void LocalizationManager::initContext(AppCore *appCore)
{
    m_appCore = appCore;
    m_isInit = true;
}

/**
 * Closes the persistence manager context
 *
 * @author Arthur
 * @date 04/02/17
 */
void LocalizationManager::closeContext()
{
    m_isInit = false;
    m_appCore = nullptr;
}

/**
 * Checks if persistence context is valid,
 * takes the necessary measures otherwise
 *
 * @author Arthur
 * @date 11/02/17
 */
void LocalizationManager::checkContext()
{
    if (m_isInit && m_appCore != nullptr)
        Logger::printInfoOnConsole("Localization context verified");
    else
    {
        Logger::printErrorOnConsole("Localization context check failed, please init it first...");
        throw PersistenceException();
    }
}

/**
 * Retrieves a localized string for a given label.
 * Allows abstraction of the internationalization storage system
 *
 * @param label the label to describe the string
 * @return the localized string
 *
 * @author Arthur
 * @date 04/01/17 - 11/02/18
 */
string LocalizationManager::fetchLocalizedString(const string &label)
{
    try
    {
        LocalizationManager::checkContext();

        string currentLocaleFile = getLanguageFile();
        return XMLHelper::loadLabeledString(currentLocaleFile, label); //TODO: recover xml once instead
    }
    catch (const LocalizationException& e)
    {
        Logger::printErrorOnConsole(e.what() + string("Localization checking failure, applying default language"));
        return XMLHelper::loadLabeledString(ENGLISH_STRINGS, label);;
    }
}


//------------------------------------------------
//          PRIVATE METHODS
//------------------------------------------------

/**
 * Retrieves language file following app language
 *
 * @return the adequate language file
 *
 * @author Arthur
 * @date ?? - 11/02/18
 */
string LocalizationManager::getLanguageFile()
{
    if (m_appCore->getLanguage() == ENGLISH)
        return ENGLISH_STRINGS;
    else if (m_appCore->getLanguage() == FRENCH)
        return FRENCH_STRINGS;
    else if (m_appCore->getLanguage() == SPANISH)
        return SPANISH_STRINGS;
    else
        return ENGLISH_STRINGS; //Default
}
