#include "../header/Settings.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 20/05
*********************************************/
Settings::Settings(DataBase *data) :  m_dataBase{data}
{
    m_dataBase->updateActivatedItemsArray();
    checkItemsAvailability();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 20/05
*********************************************/
Settings::~Settings()
{ }


/********************************************
    Getters
*********************************************
    @author Arthur  @date 20/05 - 21/05
*********************************************/
DataBase *Settings::getDataBase() const { return m_dataBase; }
bool Settings::getMorphSkinAvailability() const { return m_morphSkinIsAvailable; }
bool Settings::getCapsuleSkinAvailability() const { return m_capsuleSkinIsAvailable; }

/********************************************
    Change app language
*********************************************
    @author Arthur  @date 16/05
*********************************************/
void Settings::changeLanguage(string lang)
{
    m_dataBase->setLanguage(lang);
}

/********************************************
    Change ball skin
*********************************************
    @author Arthur  @date 20/05
*********************************************/
void Settings::changeBallSkin(string skin)
{
    m_dataBase->setBallSkin(skin);
}


/********************************************
    Check all customization items availability
*********************************************
    @author Arthur  @date 21/05
*********************************************/
void Settings::checkItemsAvailability()
{
    if ( m_dataBase->getActivatedItemsArray().empty() == true )
    {
        //no need to find if array is empty
        m_morphSkinIsAvailable = false;
        m_capsuleSkinIsAvailable = false;
    }
    else
    {
        //check in array if a bought item is present and update the variable value
        if ( m_dataBase->getActivatedItemsArray().find("morphing")
            == m_dataBase->getActivatedItemsArray().end() )
            m_morphSkinIsAvailable = false;
        else
            m_morphSkinIsAvailable = true;

        if ( m_dataBase->getActivatedItemsArray().find("capsule")
            == m_dataBase->getActivatedItemsArray().end() )
            m_capsuleSkinIsAvailable = false;
        else
            m_capsuleSkinIsAvailable = true;
    }
}
