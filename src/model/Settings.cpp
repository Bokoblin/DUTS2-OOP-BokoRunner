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
 * @date 21/05/16
 */
void Settings::checkItemsAvailability()
{
    if (m_dataBase->getActivatedItemsArray().empty())
    {
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

/**
 * Next Step
 * @author Arthur
 * @date 29/01
 */
void Settings::nextStep()
{}