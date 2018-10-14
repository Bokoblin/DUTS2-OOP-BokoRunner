#include "ShopModel.h"

using std::string;
using std::stoi;
using std::vector;
using Bokoblin::SimpleLogger::Logger;

//------------------------------------------------
//          CONSTRUCTOR / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs a Settings model with app core
 *
 * @param appCore the app's core singleton
 *
 * @author Arthur
 * @date 11/05/16 - 14/10/18
 */
ShopModel::ShopModel(AppCore* appCore) : AbstractModel(appCore)
{
    PersistenceManager::fetchConfiguration();
    PersistenceManager::fetchActivatedBonus();
    PersistenceManager::fetchShopItems();
}


/**
 * Destructor
 * @author Arthur
 * @date 11/05/16 - 13/10/18
 */
ShopModel::~ShopModel() = default;


//------------------------------------------------
//          GETTERS
//------------------------------------------------

vector<ShopItem*> ShopModel::getShopItemsArray() const { return m_appCore->getShopItemsArray(); }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Buys an item
 *
 * @param item the item to buy
 *
 * @author Arthur
 * @date 11/05/16 - 04/01/17
 */
bool ShopModel::buyItem(ShopItem* item)
{
    if (!item->isBought() && item->getPrice() <= m_appCore->getWallet()) {
        //=== update objects

        m_appCore->decreaseWallet(item->getPrice());
        item->buy();

        //=== update config files

        m_appCore->addNewActivatedBonus(item->getId());
        PersistenceManager::updatePersistence();

        return true;
    }

    return false;
}


/**
 * Next Step
 *
 * @author Arthur
 * @date 29/01/17
 */
void ShopModel::nextStep()
{}


/**
 * Quits shop by saving configuration
 *
 * @author Arthur
 * @date 03/11/17
 */
void ShopModel::quit()
{
    PersistenceManager::updatePersistence();
}

