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
 * @date 11/05/16 - 04/02/18
 */
ShopModel::ShopModel(AppCore* appCore) : AbstractModel(appCore)
{
    PersistenceManager::fetchConfiguration();
    PersistenceManager::fetchActivatedBonus();
    fetchBuyableItemsFromFile(); //FIXME
}


/**
 * Destructor
 * @author Arthur
 * @date 11/05/16 - 18/05/16
 */
ShopModel::~ShopModel()
{
    for (ShopItem* shopItem: m_shopItemsArray) {
        delete shopItem;
    }
}


//------------------------------------------------
//          GETTERS
//------------------------------------------------

vector<ShopItem*> ShopModel::getShopItemsArray() const { return m_shopItemsArray; }


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
        PersistenceManager::updatePersistence(); //FIXME: Needed by shopView for retrieval from file

        return true;
    }

    return false;
}


/**
 * Fetches Shop Items from file
 *
 * @author Arthur
 * @date 11/05/16 - 11/02/18
 */
void ShopModel::fetchBuyableItemsFromFile()
{
    try {
        PersistenceManager::checkContext();

        //FIXME: No config file / xml access should be allowed ! It breaks persistence abstraction !!
        //TODO: populate a ShopItem list from app core in Persistence manager

        pugi::xml_document doc;
        doc.load_file(m_appCore->getConfigFile().c_str());

        pugi::xml_node shop = doc.child("runner").child("shop");

        for (pugi::xml_node shopItem: shop.children("shopItem")) {
            //Updates item's attributes
            string id = shopItem.attribute("id").value();
            string name = LocalizationManager::fetchLocalizedString(id + "_name");
            string desc = LocalizationManager::fetchLocalizedString(id + "_desc");
            int price = stoi(shopItem.attribute("price").value());
            bool isBought = ((string) shopItem.attribute("bought").value()) == "true";

            //Adds item to array
            m_shopItemsArray.push_back(new ShopItem(id, name, desc, price, isBought));
        }
    }
    catch (const PersistenceException& e) {
        Logger::printErrorOnConsole(e.what() + string("Persistence checking failure, no bonus were fetched"));
    }
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

