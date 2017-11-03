#include "Settings.h"

using namespace std;

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
Settings::~Settings()
{ }


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
 * @param lang the new language
 */
void Settings::changeLanguage(string lang)
{
    m_dataBase->setLanguage(lang);
}

/**
 * Changes ball skin
 * @author Arthur
 * @date 20/05/16
 *
 * @param skin the new skin
 */
void Settings::changeBallSkin(string skin)
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
void Settings::openURLinBrowser(string url)
{
#if defined __linux__
    string command = "x-www-browser " + url;
    system(command.c_str());
#elif _WIN32
    ShellExecute(0, 0, url.c_str(), 0, 0 , SW_SHOW );
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
 */
void Settings::quit()
{
    m_dataBase->pushConfigurationToFile();
}

