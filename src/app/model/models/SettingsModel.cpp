#include "SettingsModel.h"

using std::string;

//------------------------------------------------
//          CONSTRUCTOR / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs a Settings model with app core
 *
 * @param appCore the app's core singleton
 *
 * @author Arthur
 * @date 20/05/16 - 04/02/18
 */
SettingsModel::SettingsModel(AppCore *appCore) :  AbstractModel(appCore), m_currentPage{CONFIG}
{
    PersistenceManager::fetchActivatedBonus();
    checkItemsAvailability();
}


/**
 * Destructor
 * @author Arthur
 * @date 20/05/16
 */
SettingsModel::~SettingsModel() = default;


//------------------------------------------------
//          GETTERS
//------------------------------------------------

bool SettingsModel::isMorphSkinAvailable() const { return m_morphSkinIsAvailable; }
bool SettingsModel::isCapsuleSkinAvailable() const { return m_capsuleSkinIsAvailable; }
int SettingsModel::getCurrentPage() const { return m_currentPage; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void SettingsModel::setCurrentPage(int page) { m_currentPage = page; }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Changes app language
 * @author Arthur
 * @date 16/05/16
 *
 * @param language the new language
 */
void SettingsModel::changeLanguage(const string &language)
{
    m_appCore->setLanguage(language);
}

/**
 * Changes ball skin
 * @author Arthur
 * @date 20/05/16
 *
 * @param skin the new skin
 */
void SettingsModel::changeBallSkin(const string &skin)
{
    m_appCore->setBallSkin(skin);
}


/**
 * Checks all customization items availability
 * @author Arthur
 * @date 21/05/16 - 31/10/17
 */
void SettingsModel::checkItemsAvailability()
{
    m_morphSkinIsAvailable = m_appCore->findActivatedItem("shop_morphing");
    m_capsuleSkinIsAvailable = m_appCore->findActivatedItem("shop_capsule");
}

/**
 * Opens an URL in default browser
 * @author Arthur
 * @date 02/11/17
 */
void SettingsModel::openURLinBrowser(const string &url) const
{
#if defined __linux__
    string command = "x-www-browser " + url;
    system(command.c_str());
#elif _WIN32
    ShellExecute(nullptr, nullptr, url.c_str(), nullptr, nullptr, SW_SHOW);
#else
#error Operation not supported on your platform
#endif
}


/**
 * Next Step
 * @author Arthur
 * @date 29/01
 */
void SettingsModel::nextStep()
{}


/**
 * Quits settings by saving configuration
 *
 * @author Arthur
 * @date 03/11/17
 */
void SettingsModel::quit()
{
    PersistenceManager::updatePersistence();
}

