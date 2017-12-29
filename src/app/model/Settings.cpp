#include "Settings.h"

using std::string;

/**
 * Constructs a Settings model with database
 * @author Arthur
 * @date 20/05/16 - 29/01/17
 *
 * @param dataBase the common app's dataBase
 */
Settings::Settings(DataBase *dataBase) :  AbstractModel(dataBase), m_currentPage{CONFIG}
{
    m_dataBase->fetchActivatedShopItems();
    checkItemsAvailability();
}


/**
 * Destructor
 * @author Arthur
 * @date 20/05/16
 */
Settings::~Settings() = default;


//=== Getters & Setters

bool Settings::isMorphSkinAvailable() const { return m_morphSkinIsAvailable; }
bool Settings::isCapsuleSkinAvailable() const { return m_capsuleSkinIsAvailable; }
int Settings::getCurrentPage() const { return m_currentPage; }

void Settings::setCurrentPage(int page) { m_currentPage = page; }


/**
 * Changes app language
 * @author Arthur
 * @date 16/05/16
 *
 * @param language the new language
 */
void Settings::changeLanguage(const string &language)
{
    m_dataBase->setLanguage(language);
}

/**
 * Changes ball skin
 * @author Arthur
 * @date 20/05/16
 *
 * @param skin the new skin
 */
void Settings::changeBallSkin(const string &skin)
{
    m_dataBase->setBallSkin(skin);
}


/**
 * Checks all customization items availability
 * @author Arthur
 * @date 21/05/16 - 31/10/17
 */
void Settings::checkItemsAvailability()
{
    m_morphSkinIsAvailable = m_dataBase->findActivatedItem("shop_morphing");
    m_capsuleSkinIsAvailable = m_dataBase->findActivatedItem("shop_capsule");
}

/**
 * Opens an URL in default browser
 * @author Arthur
 * @date 02/11/17
 */
void Settings::openURLinBrowser(const string &url) const {
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
void Settings::nextStep()
{}


/**
 * Quits settings by saving configuration
 *
 * @author Arthur
 * @date 03/11/17
 */
void Settings::quit()
{
    m_dataBase->pushConfigurationToFile();
}

