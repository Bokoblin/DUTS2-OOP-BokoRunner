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
 * @brief Inits the app persistence manager context
 * and the persistence system
 *
 * @author Arthur
 * @date 04/02/17
 */
void LocalizationManager::initContext(AppCore* appCore)
{
    m_appCore = appCore;
    m_isInit = true;
}

/**
 * @brief Closes the persistence manager context
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
 * @brief Checks if persistence context is valid,
 * @details takes the necessary measures otherwise
 *
 * @author Arthur
 * @date 11/02/17
 */
void LocalizationManager::checkContext()
{
    if (m_isInit && m_appCore != nullptr) {
        Logger::printInfoOnConsole("Localization context verified");
    } else {
        Logger::printErrorOnConsole("Localization context check failed, please init it first...");
        throw PersistenceException();
    }
}

/**
 * @brief Retrieves a localized string for a given label.
 * @details Allows abstraction of the internationalization storage system
 *
 * @param label the label to describe the string
 * @return the localized string
 *
 * @author Arthur
 * @date 04/01/17 - 17/07/18
 */
string LocalizationManager::fetchLocalizedString(const string& label)
{
    string result = "UNDEFINED";
    try {
        LocalizationManager::checkContext();

        string currentLocaleFile = getLanguageFile();
        result = XMLHelper::loadLabeledString(currentLocaleFile, label);
    } catch (const LocalizationException& e) {
        Logger::printErrorOnConsole(e.what() + string("Localization checking failure, applying default language"));
        result = XMLHelper::loadLabeledString(ENGLISH_STRINGS, label);;
    }

    if (result == "<" + label + ">" || result == "UNDEFINED") {
        Logger::printWarningOnConsole("No string was found for expression \"" + label + "\"");
    }

    return result;
}


//------------------------------------------------
//          PRIVATE METHODS
//------------------------------------------------

/**
 * @brief Retrieves language file following app language
 *
 * @return the adequate language file
 *
 * @author Arthur
 * @date 11/02/18
 */
string LocalizationManager::getLanguageFile()
{
    if (m_appCore->getLanguage() == ENGLISH) {
        return ENGLISH_STRINGS;
    } else if (m_appCore->getLanguage() == FRENCH) {
        return FRENCH_STRINGS;
    } else if (m_appCore->getLanguage() == SPANISH) {
        return SPANISH_STRINGS;
    } else {
        return ENGLISH_STRINGS; //Default
    }
}
