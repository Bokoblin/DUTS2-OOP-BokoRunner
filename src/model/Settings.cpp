#include "Settings.h"

using namespace std;

/**
 * Constructs a Settings model with database
 * @author Arthur
 * @date 20/05/16 - 22/12/16
 *
 * @param dataBase the common app's dataBase
 */
Settings::Settings(DataBase *dataBase) :
        m_dataBase{dataBase}, m_currentPage{CONFIG}
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

DataBase *Settings::getDataBase() const { return m_dataBase; }
bool Settings::getMorphSkinAvailability() const { return m_morphSkinIsAvailable; }
bool Settings::getCapsuleSkinAvailability() const { return m_capsuleSkinIsAvailable; }
int Settings::getCurrentPage() const { return m_currentPage; }

void Settings::setCurrentPage(int page) { m_currentPage = page; }


/**
 * Changes app language
 * @author Arthur
 * @date 16/05/16
 *
 * @param lang the new language
 */
void Settings::changeLanguage(const string &lang)
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
void Settings::changeBallSkin(const string &skin)
{
    m_dataBase->setBallSkin(skin);
}


/**
 * Checks all customization items availability
 * @author Arthur
 * @date 21/05/16
 */
void Settings::checkItemsAvailability()
{
    if (m_dataBase->getActivatedItemsArray().empty())
    {
        //no need to find if array is empty
        m_morphSkinIsAvailable = false;
        m_capsuleSkinIsAvailable = false;
    }
    else
    {
        //check in array if a bought item is present and update the variable value
        m_morphSkinIsAvailable = !(m_dataBase->getActivatedItemsArray().find("shop_morphing")
                                   == m_dataBase->getActivatedItemsArray().end());

        m_capsuleSkinIsAvailable = !(m_dataBase->getActivatedItemsArray().find("shop_capsule")
                                     == m_dataBase->getActivatedItemsArray().end());
    }
}


